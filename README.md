# WMark - Photo Watermarking Tool

**WMark** is a Qt-based desktop application designed to help photographers and image enthusiasts add aesthetic and informative watermarks to their photos. It supports reading EXIF metadata, auto-rotation, RAW file decoding, and customizable watermark styles.

## ✨ Features

- 📷 **EXIF Extraction**: Automatically reads camera brand, model, exposure time, aperture (F-number), ISO, and focal length.
- 🔄 **Auto Orientation**: Images are auto-rotated based on EXIF orientation.
- 🖼️ **RAW File Support**: Supports RAW formats like `.CR3`, `.NEF`, `.ARW`, and `.DNG` using **LibRaw**.
- 🖌️ **Watermark Options**:
  - Mode 1: Basic bottom-white frame
  - Mode 2: Enlarged canvas layout
  - Mode 3: Blurred background with overlaid image
- 🧩 **Custom Text Format**: Two formats for watermark text (line-wise or inline).
- 🏷️ **Brand Logos**: Automatically adds corresponding camera brand logos.
- 🎨 **Text Customization**: Choose font size, alignment, and text color.
- 💾 **Export**: Save the final watermarked image as `.png`, `.jpg`, or `.bmp`.

## 📦 Dependencies

- **Qt 6** or **Qt 5** (Widgets, LinguistTools)
- [**Exiv2**](https://exiv2.org) – for reading EXIF metadata
- [**LibRaw**](https://www.libraw.org) – for decoding RAW formats
- [**OpenCV**](https://opencv.org) – for fast Gaussian blur rendering

Install dependencies using Homebrew (macOS example):

```bash
brew install exiv2 libraw opencv
