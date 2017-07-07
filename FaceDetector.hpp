#ifndef FACE_DETECTOR
#define FACE_DETECTOR

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace std;
using namespace cv;

class FaceDetector {
    public:
        virtual vector<Rect> facesFromMat(Mat frame, bool showTime = false) {}
};

class HaarCascadeDetector : public FaceDetector {
    private:
        CascadeClassifier clf;
        Size size;
        float scaleFactor;
        int minNeighbors;
        int flags;
    public:
        HaarCascadeDetector(
            float scaleFactor = 1.1, 
            int minNeighbors = 3, 
            int flags = 0 | CV_HAAR_SCALE_IMAGE, 
            int length = 30
        ) {
            this->scaleFactor = scaleFactor;
            this->minNeighbors = minNeighbors;
            this->flags = flags;
            this->size = Size(length, length);
            this->clf.load("haarcascade_frontalface_alt2.xml");
        } 
      
        vector<Rect> facesFromImage(char * imgPath) {
            Mat img = imread(imgPath);
            return this->facesFromMat(img);
        }

        vector<Rect> facesFromMat(Mat frame, bool showTime = false) {
            vector<Rect> faces;

            clock_t start, end;

            if (showTime) 
                start = clock();

            this->clf.detectMultiScale(
                frame, 
                faces, 
                this->scaleFactor, 
                this->minNeighbors,
                this->flags,
                this->size
            );

            if (showTime) {
                end = clock();
                double elapsed = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
                cout << "Time (ms): " << elapsed << endl;
            }

            return faces;
        }
};

class DlibDetector : public FaceDetector {
    private:
        dlib::frontal_face_detector clf;

    public:
        DlibDetector() {
            this->clf = dlib::get_frontal_face_detector();
        }

        vector<Rect> facesFromImage(char * imgPath) {
            Mat img = imread(imgPath);
            return this->facesFromMat(img);
        }

        vector<Rect> facesFromMat(Mat frame, bool showTime = false) {
            vector<Rect> faces;

            dlib::array2d<unsigned char> img;
            dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(frame));
            dlib::pyramid_up(img);

            vector<dlib::rectangle> dets = this->clf(img);

            for (int i = 0; i < dets.size(); ++i) {
                cout << endl << dets[i].left() << " " << dets[i].top() << " " << dets[i].right() << " " << dets[i].bottom() << endl;
                Point topLeft = Point(dets[i].left(), dets[i].top());
                Point bottomRight = Point(dets[i].right(), dets[i].bottom());
                Rect r(topLeft, bottomRight);
                faces.push_back(r);
            }

            return faces;
        }
};

#endif
