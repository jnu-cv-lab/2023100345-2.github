# 2023100345邓佳瑶-作业2.github

# 实验报告二：基于 OpenCV 的图像基本处理（C++ 实现）

## 一、实验目的

1. 在 Linux/WSL 环境下配置 C++ 与 OpenCV 开发环境的方法。  
2. 使用 OpenCV 库读取、显示、转换、保存图像。  
3. 掌握图像基本信息（尺寸、通道数、数据类型）的获取方法。  
4. 练习用 NumPy（在 Python 中）或直接使用 OpenCV + C++ 完成简单的像素操作。  

## 二、实验环境

- **操作系统**：Windows 11 + WSL 2 (Ubuntu 22.04)  
- **编译器**：g++ 11.4.0  
- **集成开发环境**：Visual Studio Code + C/C++ 扩展  
- **依赖库**：OpenCV 4.5.4（libopencv-dev）  
- **测试图片**：`test.jpg`（分辨率 1214×810，彩色 3 通道）  

## 三、实验步骤

### 1. 安装 OpenCV 库

在 WSL 终端中执行以下命令：

```bash
sudo apt update
sudo apt install libopencv-dev
```

验证安装：

```bash
pkg-config --modversion opencv4   # 输出 4.5.4
```

### 2. 编写程序（C++ ）

创建文件 `main.cpp`，完整代码如下：

```cpp
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
    std::cout << "数据类型: " << img.type() << std::endl;   // 16 对应 CV_8UC3

    // 任务3：显示原图
    cv::imshow("原图", img);
    cv::waitKey(0);

    // 任务4：转换为灰度图并显示
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("灰度图", gray);
    cv::waitKey(0);

    // 任务5：保存灰度图
    cv::imwrite("gray.jpg", gray);
    std::cout << "灰度图已保存为 gray.jpg" << std::endl;

    // 任务6：输出左上角像素值（BGR顺序）
    cv::Vec3b pixel = img.at<cv::Vec3b>(0, 0);
    std::cout << "左上角像素 (B, G, R): " 
              << (int)pixel[0] << ", " 
              << (int)pixel[1] << ", " 
              << (int)pixel[2] << std::endl;

    cv::destroyAllWindows();
    return 0;
}
```

### 3. 编译程序

使用 `pkg-config` 自动获取 OpenCV 的头文件和库路径：

```bash
g++ -o main main.cpp $(pkg-config --cflags --libs opencv4)
```

编译成功后生成可执行文件 `main`。

### 4. 运行测试

将测试图片 `test.jpg` 放在同一目录下，执行：

```bash
./main test.jpg
```

## 四、实验结果

### 1. 终端输出

```
图像尺寸: 1214 x 810
通道数: 3
数据类型: 16
灰度图已保存为 gray.jpg
左上角像素 (B, G, R): 13, 0, 24
```

（实际像素值根据图片内容有所不同）

### 2. 生成的图片

- **原图**（由 `imshow` 显示，未保存文件）  
- **灰度图**：保存为 `gray.jpg`，可在 Windows 资源管理器中打开查看。

### 3. 显示效果

程序运行后弹出两个窗口（原图和灰度图），按任意键依次关闭。 WSL 2 支持 X11 转发，图像窗口会正常显示。

## 五、问题

1. **编译时找不到 `opencv2/opencv.hpp`**  
   - 原因：未指定头文件路径。  
   - 解决：使用 `pkg-config --cflags --libs opencv4` 自动获取路径。

2. **VS Code 中代码出现红色波浪线**  
   - 原因：IntelliSense 不知道 OpenCV 头文件位置。  
   - 解决：在 `.vscode/c_cpp_properties.json` 的 `includePath` 中添加 `/usr/include/opencv4`。

3. **图像窗口无法弹出**  
   - 原因：WSL 缺少图形后端或未安装 X 服务器。  
   - 解决：可改用保存图片的方式验证处理结果（本实验已保存 `gray.jpg`）。

## 六、实验总结

本次实验成功在 WSL 中搭建了 C++ + OpenCV 开发环境，并完成了图像读取、信息输出、显示、灰度转换、保存以及像素值提取等基本操作。掌握了 `pkg-config` 管理第三方库的方法，了解了 OpenCV 中 `Mat` 对象的使用。后续可以在此基础上进行更复杂的图像处理，如滤波、边缘检测等。
