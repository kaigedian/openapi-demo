# 使用帮助

## 如何获取RSA签名

开个店API接口使用RSA_SHA265获取数字签名

C++ 可以使用 [OPENSSL](https://www.openssl.org/) 库来获取签名和验签，DEMO也是基于 [OPENSSL](https://www.openssl.org/) 实现

示例中.hpp文件，兼容 windows / linux 两种环境，但如需在 linux 中使用， [OPENSSL](https://www.openssl.org/) 需根据自己所用的平台，来进行编译。

## 快速开始

| 文件 | 备注 |
| -- | -- |
| RSATool.hpp | 工具类依赖 [OPENSSL](https://www.openssl.org/) , 提供获取签名和验签的静态方法, 直接引用即可 |
| TestRSATool.cc | 签名和验签示例代码 |
| Lib	| 包含编译好的 [OPENSSL](https://www.openssl.org/) 库相关依赖（Windows） |
