package THE1.ceng.ceng351.musicdb;
import com.mysql.cj.protocol.Resultset;

import java.sql.*;

@SuppressWarnings("Duplicates")
public class MUSICDB implements IMUSICDB{
    Connection connection = null;
    @Override
    public void initialize() {

        /*String user = "e2171940"; // TODO: Your userName
        String password = "2005dec8"; //  TODO: Your password
        String host = "144.122.71.57"; // host name
        String database = "db2171940"; // TODO: Your database name
        int port = 8084; // port */

        String url = "jdbc:mysql://144.122.71.57:8084/db2171940";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(url, "e2171940", "2005dec8");
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int createTables() {
        //user(userID:int, userName:varchar(60), email:varchar(30), password:varchar(30))
        //song(songID:int, songName:varchar(60), genre:varchar(30), rating:double, artistID:int, albumID:int)
        //artist(artistID:int, artistName:varchar(60))
        // album(albumID:int, title:varchar(60), albumGenre:varchar(30), albumRating:double, releaseDate:date, artistID:int)
        // listen(userID:int, songID:int, lastListenTime:timestamp, listenCount:int)

        int numberofTablesInserted = 0;

        //user(userID:int, userName:varchar(60), email:varchar(30), password:varchar(30))
        String createUserTable = "CREATE TABLE user (" +
                "userID INT," +
                "userName VARCHAR(60)," +
                "email VARCHAR(30)," +
                "password VARCHAR(30)," +
                "PRIMARY KEY (userID))";
        try {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(createUserTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        //artist(artistID:int, artistName:varchar(60))
        String createArtistTable = "CREATE TABLE artist (" +
                "artistID INT," +
                "artistName VARCHAR(60)," +
                "PRIMARY KEY (artistID))";
        try {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(createArtistTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        // album(albumID:int, title:varchar(60), albumGenre:varchar(30), albumRating:double, releaseDate:date, artistID:int)
        String createAlbumTable = "CREATE TABLE album (" +
                "albumID INT," +
                "title VARCHAR(60)," +
                "albumGenre VARCHAR(30)," +
                "albumRating DOUBLE," +
                "releaseDate DATE," +
                "artistID INT," +
                "PRIMARY KEY (albumID),"+
                "FOREIGN KEY (artistID) REFERENCES artist(artistID) ON DELETE CASCADE ON UPDATE CASCADE)";
        try {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(createAlbumTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        //song(songID:int, songName:varchar(60), genre:varchar(30), rating:double, artistID:int, albumID:int)
        String createSongTable = "CREATE TABLE song (" +
                "songID INT," +
                "songName VARCHAR(60)," +
                "genre VARCHAR(30)," +
                "rating DOUBLE," +
                "artistID INT," +
                "albumID INT," +
                "PRIMARY KEY (songID),"+
                "FOREIGN KEY (artistID) REFERENCES artist(artistID) ON DELETE CASCADE ON UPDATE CASCADE,"+
                "FOREIGN KEY (albumID) REFERENCES album(albumID) ON DELETE CASCADE ON UPDATE CASCADE)";
        try {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(createSongTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        // listen(userID:int, songID:int, lastListenTime:timestamp, listenCount:int)
        String createListenTable = "CREATE TABLE listen (" +
                "userID INT," +
                "songID INT," +
                "lastListenTime TIMESTAMP," +
                "listenCount INT," +
                "PRIMARY KEY (userID, songID),"+
                "FOREIGN KEY (userID) REFERENCES user(userID) ON DELETE CASCADE ON UPDATE CASCADE,"+
                "FOREIGN KEY (songID) REFERENCES song(songID) ON DELETE CASCADE ON UPDATE CASCADE)";
        try {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(createListenTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofTablesInserted;
    }

    @Override
    public int dropTables() {
        int numberofTablesDropped = 0;

        String DropListenTable = "DROP TABLE IF EXISTS listen";
        try
        {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(DropListenTable);
            numberofTablesDropped++;
            statement.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        String DropSongTable = "DROP TABLE IF EXISTS song";
        try
        {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(DropSongTable);
            numberofTablesDropped++;
            statement.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        String DropAlbumTable = "DROP TABLE IF EXISTS album";
        try
        {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(DropAlbumTable);
            numberofTablesDropped++;
            statement.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        String DropArtistTable = "DROP TABLE IF EXISTS artist";
        try
        {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(DropArtistTable);
            numberofTablesDropped++;
            statement.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        String DropUserTable = "DROP TABLE IF EXISTS user";
        try
        {
            Statement statement = this.connection.createStatement();
            statement.executeUpdate(DropUserTable);
            numberofTablesDropped++;
            statement.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }
        return numberofTablesDropped;
    }

    @Override
    public int insertAlbum(Album[] albums) {
        int result = 0;
        String insertAlbumTable = "INSERT INTO album(albumID, title, albumGenre, albumRating, releaseDate, artistID) VALUES (?, ?, ?, ?, ?, ?)";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(insertAlbumTable);
            for(Album album : albums)
            {
                ppSt.setInt(1, album.getAlbumID());
                ppSt.setString(2, album.getTitle());
                ppSt.setString(3, album.getAlbumGenre());
                ppSt.setDouble(4, album.getAlbumRating());
                ppSt.setString(5, album.getReleaseDate());
                ppSt.setInt(6, album.getArtistID());

                ppSt.executeUpdate();
                result++;
            }
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public int insertArtist(Artist[] artists) {
        int result = 0;
        String insertArtistTable = "INSERT INTO artist(artistID, artistName) VALUES (?, ?)";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(insertArtistTable);
            for(Artist artist : artists)
            {
                ppSt.setInt(1, artist.getArtistID());
                ppSt.setString(2, artist.getArtistName());
                ppSt.executeUpdate();
                result++;
            }
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public int insertSong(Song[] songs) {
        int result = 0;
        String insertSongTable = "INSERT INTO song(songID, songName, genre, rating, artistID, albumID) VALUES (?, ?, ?, ?, ?, ?)";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(insertSongTable);
            for(Song song : songs)
            {
                ppSt.setInt(1, song.getSongID());
                ppSt.setString(2, song.getSongName());
                ppSt.setString(3, song.getGenre());
                ppSt.setDouble(4, song.getRating());
                ppSt.setInt(5, song.getArtistID());
                ppSt.setInt(6, song.getAlbumID());

                ppSt.executeUpdate();
                result++;
            }
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public int insertUser(User[] users) {

        int result = 0;
        String insertUserTable = "INSERT INTO user (userID, userName, email, password) VALUES (?, ?, ?, ?)";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(insertUserTable);
            for(User user : users)
            {
                ppSt.setInt(1, user.getUserID());
                ppSt.setString(2, user.getUserName());
                ppSt.setString(3, user.getEmail());
                ppSt.setString(4, user.getPassword());
                ppSt.executeUpdate();
                result++;
            }
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public int insertListen(Listen[] listens) {
        int result = 0;
        String insertListenTable = "INSERT INTO listen(userID, songID, lastListenTime, listenCount) VALUES (?, ?, ?, ?)";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(insertListenTable);
            for(Listen listen : listens)
            {
                ppSt.setInt(1, listen.getUserID());
                ppSt.setInt(2, listen.getSongID());
                ppSt.setTimestamp(3, listen.getLastListenTime());
                ppSt.setInt(4, listen.getListenCount());

                ppSt.executeUpdate();
                result++;
            }
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public QueryResult.ArtistNameSongNameGenreRatingResult[] getHighestRatedSongs() {

        ResultSet rs;
        int i = 0;
        int size = 0;

        String query = "SELECT A.artistName, S.songName, S.genre, S.rating "+
                        "FROM artist A, song S "+
                        "WHERE A.artistID = S.artistID AND "+
                        "S.rating = (SELECT MAX(S2.rating) "+
                                    "FROM song S2) "+
                        "ORDER BY A.artistName ASC;";

        try
        {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);
            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
            QueryResult.ArtistNameSongNameGenreRatingResult[] result = new QueryResult.ArtistNameSongNameGenreRatingResult[size];

            while(rs.next())
            {
                String artistName = rs.getString("artistName");
                String songName = rs.getString("songName");
                String genre = rs.getString("genre");
                double rating = rs.getDouble("rating");
                result[i] = new QueryResult.ArtistNameSongNameGenreRatingResult(artistName, songName, genre, rating);
                i++;
            }
            st.close();
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public QueryResult.TitleReleaseDateRatingResult getMostRecentAlbum(String artistName) {

        ResultSet rs;

        String query = "SELECT Al.title, Al.releaseDate, Al.albumRating "+
                        "FROM album Al,artist Ar "+
                        "WHERE Al.artistID = Ar.artistID AND Ar.artistName = ? AND "+
                        "Al.releaseDate = (SELECT MAX(Al2.releaseDate) "+
                                            "FROM album Al2 "+
                                            "WHERE Al2.artistID = Al.artistID);";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setString(1, artistName);
            rs = ppSt.executeQuery();
            rs.next();

            String title = rs.getString("title");
            String releaseDate = rs.getString("releaseDate");
            double rating = rs.getDouble("albumRating");
            ppSt.close();
            return new QueryResult.TitleReleaseDateRatingResult(title, releaseDate, rating);
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public QueryResult.ArtistNameSongNameGenreRatingResult[] getCommonSongs(String userName1, String userName2) {

        ResultSet rs;
        int i = 0;
        int size = 0;
        /*String query = "SELECT A.artistName, S.songName, S.genre, S.rating "+
                        "FROM artist A, song S "+
                        "WHERE S.artistID = A.artistID AND "+
                        "S.songID IN ((SELECT L1.songID "+
                                    "FROM listen L1, user U1 "+
                                    "WHERE U1.userName = ? AND L1.userID = U1.userID) "+
                                    "INTERSECT "+
                                    "(SELECT L2.songID "+
                                    "FROM listen L2, user U2 "+
                                    "WHERE U2.userName = ? AND L2.userID = U2.userID)) "+
                        "ORDER BY S.rating DESC;";*/
        String query = "SELECT A.artistName, S.songName, S.genre, S.rating "+
                        "FROM artist A, song S "+
                        "WHERE S.artistID = A.artistID AND "+
                        "S.songID IN (SELECT L1.songID "+
                                "FROM listen L1, user U1 "+
                                "WHERE U1.userName = ? AND L1.userID = U1.userID AND S.songID IN ( "+
                                "SELECT L2.songID "+
                                "FROM listen L2, user U2 "+
                                "WHERE U2.userName = ? AND L2.userID = U2.userID)) "+
                        "ORDER BY S.rating DESC;";
        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setString(1, userName1);
            ppSt.setString(2, userName2);
            rs = ppSt.executeQuery();

            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
            QueryResult.ArtistNameSongNameGenreRatingResult[] result = new QueryResult.ArtistNameSongNameGenreRatingResult[size];

            while(rs.next())
            {
                String artistName = rs.getString("artistName");
                String songName = rs.getString("songName");
                String genre = rs.getString("genre");
                double rating = rs.getDouble("rating");
                result[i] = new QueryResult.ArtistNameSongNameGenreRatingResult(artistName, songName, genre, rating);
                i++;
            }
            ppSt.close();
            return result;
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override //TODO:
    public QueryResult.ArtistNameNumberOfSongsResult[] getNumberOfTimesSongsListenedByUser(String userName) {

        ResultSet rs;
        int i = 0;
        int size = 0;

        String query = "SELECT A.artistName, SUM(L.listenCount)\n" +
                "FROM song S, listen L, user U, artist A\n" +
                "WHERE U.userID = L.userID AND U.userName = ? AND L.songID = S.songID AND A.artistID = S.artistID\n" +
                "GROUP BY S.artistID, A.artistName;";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setString(1, userName);
            rs = ppSt.executeQuery();

            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
            QueryResult.ArtistNameNumberOfSongsResult[] result = new QueryResult.ArtistNameNumberOfSongsResult[size];

            while(rs.next())
            {
                String artistName = rs.getString("artistName");
                int numberOfSongs = rs.getInt("SUM(L.listenCount)");
                result[i] = new QueryResult.ArtistNameNumberOfSongsResult(artistName, numberOfSongs);
                i++;
            }
            ppSt.close();
            return result;
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public User[] getUsersWhoListenedAllSongs(String artistName) {

        ResultSet rs;
        int i = 0;
        int size = 0;
        String query = "SELECT * "+
                        "FROM user U "+
                        "WHERE NOT EXISTS (SELECT S.songID "+
                                            "FROM artist A, song S "+
                                            "WHERE A.artistName = ? AND "+
                                            "A.artistID = S.artistID AND "+
                                            "S.songID NOT IN "+
                                            "(SELECT L.songID "+
                                            "FROM listen L "+
                                            "WHERE L.userID = U.userID)) "+
                        "ORDER BY U.userID ASC;";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setString(1, artistName);
            rs = ppSt.executeQuery();

            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
           User[] result = new User[size];

            while(rs.next())
            {
                int userID = rs.getInt("userID");
                String userName = rs.getString("userName");
                String email = rs.getString("email");
                String password = rs.getString("password");
                result[i] = new User(userID, userName, email, password);
                i++;
            }
            ppSt.close();
            return result;
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public QueryResult.UserIdUserNameNumberOfSongsResult[] getUserIDUserNameNumberOfSongsNotListenedByAnyone() {

        ResultSet rs;
        int i = 0;
        int size = 0;
        String query = "SELECT U.userID, U.userName, COUNT(*) "+
                        "FROM user U, listen L "+
                        "WHERE U.userID = L.userID AND "+
                        "NOT EXISTS(SELECT * "+
                                    "FROM listen L2 "+
                                    "WHERE L2.userID != L.userID AND L2.songID = L.songID) "+
                        "GROUP BY U.userID "+   // FIXME: U.username eklenecek mi?
                        "ORDER BY U.userID ASC;";

        try
        {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);
            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
            QueryResult.UserIdUserNameNumberOfSongsResult[] result = new QueryResult.UserIdUserNameNumberOfSongsResult[size];

            while(rs.next())
            {
                int userID = rs.getInt("userID");
                String userName = rs.getString("userName");
                int numberOfSongs = rs.getInt("COUNT(*)");

                result[i] = new QueryResult.UserIdUserNameNumberOfSongsResult(userID, userName, numberOfSongs);
                i++;
            }
            st.close();
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return null;

    }

    @Override
    public Artist[] getArtistSingingPopGreaterAverageRating(double rating) {

        ResultSet rs;
        int i = 0;
        int size = 0;
        String query = "SELECT DISTINCT A.artistID, A.artistName "+
                        "FROM artist A, song S "+
                        "WHERE S.artistID = A.artistID AND S.genre = 'Pop' AND "+
                        "? < (SELECT AVG(S2.rating) "+
                                    "FROM song S2 "+
                                    "WHERE S2.artistID = A.artistID) "+
                        "ORDER BY A.artistID ASC;";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setDouble(1, rating);
            rs = ppSt.executeQuery();

            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
            Artist[] result = new Artist[size];

            while(rs.next())
            {
                int artistID = rs.getInt("artistID");
                String artistName = rs.getString("artistName");
                result[i] = new Artist(artistID, artistName);
                i++;
            }
            ppSt.close();
            return result;
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override //TODO:
    public Song[] retrieveLowestRatedAndLeastNumberOfListenedSongs() {

        ResultSet rs;
        int i = 0;
        int size = 0;

        String query = "SELECT S.songID,S.songName,S.genre,S.rating,S.artistID,S.albumID\n" +
                "FROM song S,listen L\n" +
                "WHERE S.genre = 'Pop' AND  L.songID = S.songID AND\n" +
                "    S.rating = (SELECT MIN(S4.rating)\n" +
                "                FROM song S4 WHERE S4.genre = 'Pop')\n" +
                "GROUP BY S.songID\n" +
                "HAVING SUM(L.listenCount) = (SELECT MIN(Temp2.sumListen2)\n" +
                "                             FROM (SELECT SUM(L2.listenCount) AS sumListen2\n" +
                "                                   FROM song S2,listen L2\n" +
                "                                   WHERE S2.genre = 'Pop' AND  L2.songID = S2.songID AND\n" +
                "                                       S2.rating = (SELECT MIN(S3.rating)\n" +
                "                                                    FROM song S3\n" +
                "                                                    WHERE S3.genre = 'Pop')\n" +
                "                                   GROUP BY S2.songID) AS Temp2)\n" +
                "ORDER BY S.songID;";

        try
        {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);
            if (rs.last()) {
                size = rs.getRow();
                rs.beforeFirst();
            }
            Song[] result = new Song[size];

            while(rs.next())
            {
                int songID = rs.getInt("songID");
                String songName = rs.getString("songName");
                String genre = rs.getString("genre");
                double rating = rs.getDouble("rating");
                int albumID = rs.getInt("albumID");
                int artistID = rs.getInt("artistID");
                result[i] = new Song(songID, songName, genre, rating, albumID, artistID);
                i++;
            }
            st.close();
            return result;
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override // FIXME: precision
    public int multiplyRatingOfAlbum(String releaseDate) {

        String query = "UPDATE album "+
                        "SET albumRating = albumRating * 1.5 "+
                        "WHERE releaseDate > ?;";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setString(1, releaseDate);

            int result = ppSt.executeUpdate();
            ppSt.close();
            return result;
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return 0;
    }

    @Override
    public Song deleteSong(String songName) {

        ResultSet rs;

        String query = "SELECT * "+
                        "FROM song "+
                        "WHERE songName = ?;";

        String query1 = "DELETE FROM song "+
                "WHERE songName = ?;";

        try
        {
            PreparedStatement ppSt = this.connection.prepareStatement(query);
            ppSt.setString(1, songName);
            rs = ppSt.executeQuery();
            rs.next();

            int songID = rs.getInt("songID");
            String songName1 = rs.getString("songName");
            String genre = rs.getString("genre");
            double rating = rs.getDouble("rating");
            int artistID = rs.getInt("artistID");
            int albumID = rs.getInt("albumID");

            Song result = new Song(songID, songName1, genre, rating, artistID, albumID);
            ppSt.close();


            PreparedStatement ppSt1 = this.connection.prepareStatement(query1);
            ppSt1.setString(1, songName);
            ppSt1.executeUpdate();
            ppSt1.close();

            return result;
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }
}
