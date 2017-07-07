#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <thread>

#include "./FaceDetector.hpp"

using namespace std;
using namespace cv;

const int N_THREADS = 10;

void drawFaces(Mat &img, vector<Rect> faces) {
    for (int i = 0; i < faces.size(); ++i) {
        rectangle(img, faces[i], Scalar(255, 0, 0), 2);
    }
}

int main()
{
    VideoCapture cap(0);

    HaarCascadeDetector haar;
    DlibDetector dlb;
    FaceDetector *detector = &dlb;

    if (!cap.isOpened()) {
        cerr << "Cannot open VideoCapture" << endl;
        return -1;
    }

    // thread *threads = new thread[N_THREADS];
    // int current = 0;

    clock_t start = 0;
    clock_t end = 0;

    while (true) {
        // Calculate Time
        start = end;
        end = clock();
        double elapsed = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
        cout << "Frame execution (ms): " << elapsed << endl;

        Mat frame, grayFrame;
        cap >> frame;
        cvtColor(frame, grayFrame, CV_BGR2GRAY);
        vector<Rect> faces = detector->facesFromMat(frame, true);

        // Draw thread
        // threads[current++] = thread(drawFaces, frame, faces);
        for (int i = 0; i < faces.size(); ++i)
            cout << faces[i] << endl;
        drawFaces(frame, faces);

        imshow("video", frame);
        if ((waitKey(1) & 0xFF) == 'q') break;

        // Join all threads
        // if (current == N_THREADS) {
        //     current = 0;
        //     for (int i = 0; i < N_THREADS; ++i)
        //         threads[i].join();
        // }
    }

    destroyAllWindows();
    cap.release();

    return 0;
}


