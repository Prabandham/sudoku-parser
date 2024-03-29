#include <iostream>
#include <regex>

#include "../lib/sudoku.h"

using namespace std; // Or using std::string;

// -----------------------------------------------------------------
// -----------------------------------------------------------------
// ------------------- from s0 to s35 ------------------------------
// -----------------------------------------------------------------
// ---------- create both features and labels files here -----------

int main(int argc, char **argv)
{

    ExtractionInformation extractInfo, extractInfo2;

    string filePath("./../assets/puzzles/s0.jpg"); // by default
    if (argc > 1)
    {
        filePath = argv[1];
    }

    Mat image = imread(filePath, 0);
 
    // prepare knn
    string raw_features_path("./../assets/config/raw-features.yml"); // created by prepareData
    cv::FileStorage raw_features(raw_features_path, cv::FileStorage::READ);
    Ptr<ml::KNearest> knn = getKnn(raw_features);

    Mat preprocessed = preprocess(image.clone(), true);
    vector<Point> bigestApprox = findBiggestBlob(preprocessed, image);

    extractInfo = extractPuzzle(image, bigestApprox);
    Mat extractedPuzzle = extractInfo.image;
    // showImage(extractedPuzzle);

    // mouline: 697
    // getknn 162
    // findBiggestBlob 35
    // recursiveExtraction 91
    // grabNumbers 128

    Mat finalExtraction = recursiveExtraction(extractedPuzzle);
    string initialStateOfTheSudoku = grabNumbers(finalExtraction, knn);

    cout << "initialStateOfTheSudoku: " << initialStateOfTheSudoku << endl;

    return 0;
}