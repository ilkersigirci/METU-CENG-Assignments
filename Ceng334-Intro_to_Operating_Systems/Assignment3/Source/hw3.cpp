#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "ext2.h"
#include <string>
#include <vector>
#include <math.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/mman.h> 
#define BASE_OFFSET 1024
#define EXT2_BLOCK_SIZE 1024
#define IMAGE "image.img"

typedef unsigned char bmap;
#define __NBITS (8 * (int) sizeof (bmap))
#define __BMELT(d) ((d) / __NBITS)
#define __BMMASK(d) ((bmap) 1 << ((d) % __NBITS))
#define BM_SET(d, set) ((set[__BMELT (d)] |= __BMMASK (d)))
#define BM_CLR(d, set) ((set[__BMELT (d)] &= ~__BMMASK (d)))
#define BM_ISSET(d, set) ((set[__BMELT (d)] & __BMMASK (d)) != 0)

unsigned int block_size = 0;
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size)
using namespace std;
vector<unsigned int> freeDataBlockBaseVec;

void parsePath(string pathes, vector<string> &pathVec){

    char delimiter = '/';
    if(pathes.find(delimiter) == std::string::npos){
        pathVec.push_back(pathes);
        return;
    }
    string path;
    stringstream ss(pathes);
    while(getline(ss, path, delimiter)) pathVec.push_back(path);     
}
unsigned int pathtoInodeNum(int fd, ext2_super_block super, vector<ext2_group_desc> groupDescriptors, char **argv){
    
    unsigned int rootInodeNum = 2; // FIXME: dogru mu?
    unsigned int rootInodeGroup = (rootInodeNum - 1) / super.s_inodes_per_group;
    unsigned int rootInodeIndex = (rootInodeNum - 1) % super.s_inodes_per_group;
    unsigned int rootInodeNumBase = groupDescriptors[rootInodeGroup].bg_inode_table*block_size + rootInodeIndex*super.s_inode_size;
    unsigned int inodeNum = 0;

    string pathes = argv[3];
    vector<string> pathVec;
    parsePath(pathes, pathVec);    
    
    unsigned int inode;
    unsigned short rec_len;
    unsigned char name_len,file_type;
    int paddedNameLength;
    ext2_inode rootInode;
    char nameChar;
    int equalFlag = 1;

    // target rootInode'a gitme
    lseek(fd, rootInodeNumBase, SEEK_SET);
    read(fd, &rootInode, super.s_inode_size);

    //goto last dir
    lseek(fd, rootInode.i_block[0]*block_size, SEEK_SET);

    while(pathVec.size()){
        equalFlag = 1;

        read(fd, &inode, sizeof(unsigned int));            
        read(fd, &rec_len, sizeof(unsigned short));
        read(fd, &name_len, sizeof(unsigned char));
        read(fd, &file_type, sizeof(unsigned char));
        paddedNameLength = ((int)name_len  & 255);
        if(paddedNameLength % 4 != 0) paddedNameLength = ((paddedNameLength / 4) + 1)*4;
        
        char name[name_len];
        for(int i = 0; i < name_len; i++){
            read(fd, &nameChar, sizeof(char));
            name[i] = nameChar;
        }
        
        string firstElement = pathVec.front();
        if(name_len == firstElement.length()){
            equalFlag = 1;
            for(int i = 0; i < name_len; i++){
                if(firstElement[i] != name[i]){
                    equalFlag = 0;
                    break;
                }
            }
            if(equalFlag){
                inodeNum = inode;
                rootInodeNum = inode;
                rootInodeGroup = (rootInodeNum - 1) / super.s_inodes_per_group;
                rootInodeIndex = (rootInodeNum - 1) % super.s_inodes_per_group;
                rootInodeNumBase = groupDescriptors[rootInodeGroup].bg_inode_table*block_size + rootInodeIndex*super.s_inode_size;
                
                lseek(fd, rootInodeNumBase, SEEK_SET);
                read(fd, &rootInode, super.s_inode_size);
                lseek(fd, rootInode.i_block[0]*block_size, SEEK_SET);  
                
                pathVec.erase(pathVec.begin());
                continue;
            }         
        }
        lseek(fd,paddedNameLength - name_len, SEEK_CUR);        
    }
    return inodeNum;
}
unsigned int getFreeInode_Block(int fd, ext2_super_block &super, vector<ext2_group_desc> &groupDescriptors, string select){
    unsigned int groupBaseIndex, groupBase = block_size*ceil((BASE_OFFSET+sizeof(super)) / float(block_size));
    if(select == "inode"){
        
        //bmap inodeBitmap[block_size];
        bmap* inodeBitmap = (bmap*) malloc(block_size);
        for (int i = 0; i < groupDescriptors.size(); i++){            
            groupBaseIndex = groupBase + i * sizeof(groupDescriptors[i]);
            lseek(fd, groupDescriptors[i].bg_inode_bitmap*block_size, SEEK_SET);
            read(fd, inodeBitmap,block_size);

            for (int j = 0; j < super.s_inodes_per_group; j++){
                if(BM_ISSET(j,inodeBitmap) == 0){
                    super.s_free_inodes_count--;
                    lseek(fd, BASE_OFFSET, SEEK_SET);
                    write(fd, &super, sizeof(super));

                    groupDescriptors[i].bg_free_inodes_count--;        
                    lseek(fd, groupBaseIndex, SEEK_SET);
                    write(fd, &(groupDescriptors[i]), sizeof(groupDescriptors[i]));

                    BM_SET(j,inodeBitmap);
                    lseek(fd, groupDescriptors[i].bg_inode_bitmap*block_size, SEEK_SET);
                    write(fd, inodeBitmap,block_size);
                    return 1 + j + (i * super.s_inodes_per_group);
                }
            }    
        }
        free(inodeBitmap);    
    }
    else if(select == "block"){
        //bmap blockBitmap[block_size];
        bmap* blockBitmap = (bmap*) malloc(block_size);
        for (int i = 0; i < groupDescriptors.size(); i++){
            groupBaseIndex = groupBase + i * sizeof(groupDescriptors[i]);
            lseek(fd, groupDescriptors[i].bg_block_bitmap*block_size, SEEK_SET);
            read(fd, blockBitmap,block_size);

            for (int j = 0; j < super.s_blocks_per_group; j++){
                if(BM_ISSET(j,blockBitmap) == 0){
                    super.s_free_blocks_count--;
                    lseek(fd, BASE_OFFSET, SEEK_SET);
                    write(fd, &super, sizeof(super));

                    groupDescriptors[i].bg_free_blocks_count--;         
                    lseek(fd, groupBaseIndex, SEEK_SET);
                    write(fd, &(groupDescriptors[i]), sizeof(groupDescriptors[i]));

                    BM_SET(j,blockBitmap);
                    lseek(fd, groupDescriptors[i].bg_block_bitmap*block_size, SEEK_SET);
                    write(fd, blockBitmap,block_size);
                    return super.s_first_data_block + j + super.s_blocks_per_group*i;                
                }
            }    
        }
        free(blockBitmap); 
    }
    
    return -1; // No free inode or block found    
}
void fillReservedInode(int fd, ext2_super_block super, vector<ext2_group_desc> groupDescriptors, unsigned int reservedInodeNum, char **argv){
    int reservedInodeGroup = (reservedInodeNum - 1) / super.s_inodes_per_group;
    int reservedInodeIndex = (reservedInodeNum - 1) % super.s_inodes_per_group;
    unsigned int reservedInodeNumBase = groupDescriptors[reservedInodeGroup].bg_inode_table*block_size + reservedInodeIndex*super.s_inode_size;
    struct stat sourceStat;
    ext2_inode reservedInode;

    stat(argv[2], &sourceStat);

    reservedInode.i_mode        = sourceStat.st_mode;        
    reservedInode.i_uid         = sourceStat.st_uid & 0xFFFF;         
    reservedInode.i_size        = sourceStat.st_size;       
    reservedInode.i_atime       = sourceStat.st_atime;      
    reservedInode.i_ctime       = sourceStat.st_ctime;    
    reservedInode.i_mtime       = sourceStat.st_mtime;      
    reservedInode.i_dtime       = 0;      
    reservedInode.i_gid         = sourceStat.st_gid & 0xFFFF;         
    reservedInode.i_links_count = sourceStat.st_nlink;
    reservedInode.i_blocks      = block_size/512*ceil(sourceStat.st_size/(float)block_size);
    reservedInode.i_flags       = 0;      
    reservedInode.osd1          = 0;         
    for (int i = 0; i < 15; i++) reservedInode.i_block[i] = 0; //sonradan doldurulacak
    reservedInode.i_generation  = 0; 
    reservedInode.i_file_acl    = 0;   
    reservedInode.i_dir_acl     = 0;    
    reservedInode.i_faddr       = 0;
    for (int i = 0; i < 3; i++) reservedInode.extra[i] = 0;    

    lseek(fd, reservedInodeNumBase, SEEK_SET);
    write(fd, &reservedInode, super.s_inode_size);
}
void createDirectory(int fd, ext2_super_block &super, vector<ext2_group_desc> &groupDescriptors, unsigned int reservedInodeNum, char **argv){
    
    unsigned int inodeNum;
    string pathorNum = argv[3];
    int first = pathorNum[0] - '0';
    if((first>= 0) && (first <= 9)) inodeNum = stoi(pathorNum);
    else inodeNum = pathtoInodeNum(fd, super, groupDescriptors, argv);

    unsigned int inodeGroup = (inodeNum - 1) / super.s_inodes_per_group;
    unsigned int inodeIndex = (inodeNum - 1) % super.s_inodes_per_group;
    unsigned int inodeNumBase = groupDescriptors[inodeGroup].bg_inode_table*block_size + inodeIndex*super.s_inode_size;
    
    unsigned int inode;
    unsigned short rec_len, actual_rec_len,remaining_rec_len;
    unsigned char name_len,file_type;
    int paddedNameLength, targetInodeBlockIndex = 0;
    ext2_inode targetInode;
    string sourceName = argv[2];
    char nameChar;

    // target inode'a gitme
    lseek(fd, inodeNumBase, SEEK_SET);
    read(fd, &targetInode, super.s_inode_size);

    //goto last dir
    lseek(fd, targetInode.i_block[0]*block_size, SEEK_SET);
    while(true){
        read(fd, &inode, sizeof(unsigned int));            
        read(fd, &rec_len, sizeof(unsigned short));
        read(fd, &name_len, sizeof(unsigned char));
        read(fd, &file_type, sizeof(unsigned char));
        paddedNameLength = ((int)name_len  & 255);
        if(paddedNameLength%4 != 0) paddedNameLength = ((paddedNameLength / 4) + 1)*4;
        actual_rec_len  = 8 + paddedNameLength;        
        if(rec_len > actual_rec_len){
            remaining_rec_len = rec_len - actual_rec_len;   
            rec_len = actual_rec_len;
            lseek(fd, targetInode.i_block[0]*block_size+targetInodeBlockIndex+4, SEEK_SET);          
            write(fd, &rec_len, sizeof(unsigned short));
            targetInodeBlockIndex += rec_len;
            break;
        }
        else{
            lseek(fd,paddedNameLength,SEEK_CUR);
            targetInodeBlockIndex += rec_len;
        }
    }

    //set elements of new dir    
    file_type = EXT2_FT_REG_FILE;
    //file_type = 2;
    name_len  = sourceName.length();

    lseek(fd, targetInode.i_block[0]*block_size+targetInodeBlockIndex, SEEK_SET);
    write(fd, &reservedInodeNum, sizeof(unsigned int));            
    write(fd, &remaining_rec_len, sizeof(unsigned short));
    write(fd, &name_len, sizeof(unsigned char));
    write(fd, &file_type, sizeof(unsigned char));

    for (int i = 0; i < name_len; i++)
    {
        nameChar = sourceName[i];
        write(fd, &nameChar, sizeof(char));
    }    
}
void copyDataBlocks(int fd, int fd2, ext2_super_block &super, vector<ext2_group_desc> &groupDescriptors, unsigned int reservedInodeNum, char **argv){
    bmap sourceDataByte;
    int reservedInodeGroup = (reservedInodeNum - 1) / super.s_inodes_per_group;
    int reservedInodeIndex = (reservedInodeNum - 1) % super.s_inodes_per_group;
    unsigned int reservedInodeNumBase = groupDescriptors[reservedInodeGroup].bg_inode_table*block_size + reservedInodeIndex*super.s_inode_size;
    unsigned int freeDataBlockBase;
   
    struct stat sourceStat;
    ext2_inode reservedInode;
    unsigned int sourceSize;
    int flag;   

    stat(argv[2], &sourceStat);
    sourceSize = sourceStat.st_size;

    lseek(fd, reservedInodeNumBase, SEEK_SET); // reserved inode'a gitme
    read(fd, &reservedInode, super.s_inode_size);

    lseek(fd2, 0, SEEK_SET);
    //copy data blocks
    for (int i = 0; i < 12; i++){

        freeDataBlockBase = getFreeInode_Block(fd, super, groupDescriptors, "block");
        reservedInode.i_block[i] = freeDataBlockBase;
        freeDataBlockBaseVec.push_back(freeDataBlockBase);
        //cout << "freeDataBlockBase " << freeDataBlockBase << endl;

        for (int j = 0; j < block_size; j++){
            if((sourceSize) == 0){
                flag = 1;
                break;
            }
            //lseek(fd2, j+i*block_size, SEEK_SET);
            read(fd2, &sourceDataByte, sizeof(bmap));        
            lseek(fd, block_size*freeDataBlockBase+j, SEEK_SET);
            write(fd, &sourceDataByte, sizeof(bmap));
            sourceSize--;
        }
        if(flag) break;    
    }
    lseek(fd, reservedInodeNumBase, SEEK_SET);
    write(fd, &reservedInode, super.s_inode_size);

    for (int i = 0; i < freeDataBlockBaseVec.size() - 1; i++) cout << freeDataBlockBaseVec[i] << ",";
    cout << freeDataBlockBaseVec.back() << endl;
    
}

int main(int argc, char **argv){
    
    int N;
    unsigned int fd, fd2, groupCount, sourceSize;
    unsigned int groupBase, reservedInodeNum;
    vector<ext2_group_desc> groupDescriptors;
    fd  = open(argv[1], O_RDWR);
    fd2 = open(argv[2], O_RDONLY);  
    ext2_super_block super;
    ext2_group_desc group;

    //set super
    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super, sizeof(super));

    //variable initilizations
    groupCount = ceil(super.s_inodes_count / float(super.s_inodes_per_group));
    block_size = 1024 << super.s_log_block_size;
    groupBase = block_size*ceil((BASE_OFFSET+sizeof(super)) / float(block_size));
    
    //set groupDescriptors
    lseek(fd, groupBase, SEEK_SET);
    for(int i = 0; i < groupCount; i++){
        read(fd, &group, sizeof(group));
        groupDescriptors.push_back(group);
    }

    reservedInodeNum = getFreeInode_Block(fd, super, groupDescriptors, "inode");
    cout << reservedInodeNum << " ";
    fillReservedInode(fd, super, groupDescriptors, reservedInodeNum, argv);
    createDirectory  (fd, super, groupDescriptors, reservedInodeNum, argv);
    copyDataBlocks   (fd, fd2, super, groupDescriptors, reservedInodeNum, argv);    

    close(fd);
    close(fd2);

    return 0;
}