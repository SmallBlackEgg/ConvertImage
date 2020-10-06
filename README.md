## 使用说明

## 一、功能介绍

#### 1.1 格式转换功能

实现了YUV420< == >BMP和YUV420SP(NV12)< == >BMP的互相转换，通过配置文件可控制不同的转换格式，以及图片的输出格式。此功能解决了使用其他脚本进行单线程转换造成的效率低下问题，以及转换格式单一等问题。

#### 1.2 在线查看功能

实现了对YUV420和YUV420SP(NV12)进行查看，通过配置文件可以控制两种格式的显示。此功能解决了对YUV格式的图片查看需要先进行转换才能查看的问题，在现实过程中对图片的名称进行打印，方便对图片的挑选。

#### 1.3 其他功能

* 实现了对图片文件进行裁剪和缩放功能，通过配置文件可以控制输出图片的大小以及缩放比例，丰富该软件的功能。

#### 1.4 系统支持

此软件适配的系统为ubuntu和osx。

## 二、配置文件介绍

#### 2.1 配置文件介绍

```json
{
  "convert" :
  {
    "file_path_in" : 图片输入路径。char类型，最高支持256字节长度的路径
    "file_path_out" : 图片输出大小。char类型，最高支持256字节长度的路径
    "image_height" : 输入图片的高。uint32_t类型
    "image_width" : 输入图片的宽。uint32_t类型
    "convert_in" : 输入图片的格式，目前支持“yuv”和“bmp”，默认格式为“yuv”。char类型
    "is_yuv420": 输入图片的格式是否是YUV420。true:YUV420，false:YUV420SP(NV12)，默认为true。bool类型
    "convert_out" : 输出图片的格式，目前支持“bm。”。char类型
    "thread_num" : 转换图片需要的线程，默认为单线程。若想加快转换速度，可以适当增加开辟的线程数量。uint32_t类型
    "is_cut" : 输出图片是否进行裁剪操作。bool类型
    "is_resize" : 输出图片是否进行缩放操作。bool类型
  },
  "cut" :
  {
    "bottom" : 输入图片底部裁剪像素大小。uint32_t类型
    "left" : 输入图片左边裁剪像素大小。uint32_t类型
    "right" : 输入图片右边裁剪像素大小。uint32_t类型
    "top" : 输入图片上部裁剪像素大小。uint32_t类型
  },
  "resize" :
  {
    "height" : 输出图片的高度。uint32_t类型
    "width" : 输出图片的宽度。uint32_t类型
  }
}
```

#### 2.2 格式转换配置

格式转换配置需要依赖2.1中的所有参数设置，`is_cut`、`is_resize`两个开关控制格式转换的附加功能，默认情况下是关闭的。

#### 2.3 在线查看配置

在线查看配置只需要依赖2.2中的`file_path_in`、`image_width`、`image_height`、`convert_in`、`is_yuv420`参数设置。

#### 2.4 注意事项

* 裁剪和缩放需要依赖convert配置中的`is_cut`和`is_resize`配置

## 三 、如何构建

#### 3.1 如何编译

```shell
mkdir build
cd build
cmake ../
make -j8
```

#### 3.2 如何打包

```shell
./package.sh platform[linux|osx]
```

#### 3.3 如何运行

##### 3.3.1 解压软件包

```shell
#platform为Linux或Darwin
tar -xvf image_tools_platform.tar.gz
```

##### 3.3.2 运行

```shell
cd scripts
./run_convert.sh #图片转换脚本
./run_live_yuv.sh #YUV图片在线查看脚本
./run_benchmark.sh #函数性能测试脚本
```

## 四、遗留问题(BUG)

* 编译出来的PreProcessFileTest可执行文件不能正确的运行在osx系统中的terminal中，但是在Clion中使用自带的terminal缺不会出现这种情况。Linux下也没有这种现象产生。