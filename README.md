# FaceDetectionTest
Face Detection Test with Haar Cascade and Dlib Face Landmark Algorithm

## Performance:
**Intel Core I5, 6GB RAM**
Haar Cascade (using `haarcascade_frontalface_alt2.xml`): 366.82s/frame
Dlib Face Landmark Detection: 402.777s/frame

## TODO
Use C++11 thread

## How to run

- Install `OpenCV` and `Dlib` for C++
- Compile using `g++`:
```
g++ faceVideo.cpp -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_objdetect -lopencv_videoio -lopencv_objdetect -lpthread -ldlib -lgif -O3 -o faceVideo
```
- Run: `./faceVideo`
