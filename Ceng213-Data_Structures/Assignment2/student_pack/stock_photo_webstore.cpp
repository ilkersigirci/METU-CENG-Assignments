#include "stock_photo_webstore.hpp"

StockPhotoWebstore::StockPhotoWebstore() {}

StockPhotoWebstore &StockPhotoWebstore::addPhoto(const Photo &photo) {
    tpbst.insert(photo.getCategory(), photo.getName(), photo);

    return *this; // do not edit this line.
}

StockPhotoWebstore &StockPhotoWebstore::removePhoto(const std::string &category, const std::string &name) {
    tpbst.remove(category, name);

    return *this; // do not edit this line.
}

StockPhotoWebstore &StockPhotoWebstore::updatePrice(const std::string &category, const std::string &name, int newPrice) {
    Photo * curPhoto = tpbst.find(category, name);
    curPhoto->setPrice(newPrice);

    return *this; // do not edit this line.
}

StockPhotoWebstore &StockPhotoWebstore::printAllPhotos() {
    tpbst.print();

    return *this; // do not edit this line.
}

StockPhotoWebstore &StockPhotoWebstore::printAllPhotosInCategory(const std::string &category) {
    tpbst.print(category);

    return *this; // do not edit this line.
}

StockPhotoWebstore &StockPhotoWebstore::printPhoto(const std::string &category, const std::string &name) {
    tpbst.print(category, name);

    return *this; // do not edit this line.
}