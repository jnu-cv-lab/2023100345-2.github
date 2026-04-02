#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // 检查命令行参数
    if (argc != 2) {
        std::cout << "用法: ./main 图片路径" << std::endl;
        return -1;
    }

    // 任务1：读取图片
    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cout << "无法读取图片: " << argv[1] << std::endl;
        return -1;
    }

    // 任务2：输出基本信息
    std::cout << "图像尺寸: " << img.cols << " x " << img.rows << std::endl;
    std::cout << "通道数: " << img.channels() << std::endl;
    // 数据类型：CV_8U, CV_8UC3 等，这里输出整数代码
    std::cout << "数据类型: " << img.type() << std::endl;

    // 任务3：显示原图
    cv::imshow("原图", img);
    cv::waitKey(0);  // 等待按键

    // 任务4：转换为灰度图
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("灰度图", gray);
    cv::waitKey(0);

    // 任务5：保存灰度图
    cv::imwrite("gray.jpg", gray);
    std::cout << "灰度图已保存为 gray.jpg" << std::endl;

    // 任务6：简单操作 - 输出左上角像素值（BGR顺序）
    cv::Vec3b pixel = img.at<cv::Vec3b>(0, 0);
    std::cout << "左上角像素 (B, G, R): " 
              << (int)pixel[0] << ", " 
              << (int)pixel[1] << ", " 
              << (int)pixel[2] << std::endl;

    // 或者裁剪左上角 100x100 区域并保存（注释掉上面输出像素，或者二选一）
    // cv::Rect roi(0, 0, 100, 100);
    // cv::Mat crop = img(roi);
    // cv::imwrite("crop.jpg", crop);
    // std::cout << "裁剪区域已保存为 crop.jpg" << std::endl;

    cv::destroyAllWindows();
    return 0;
}