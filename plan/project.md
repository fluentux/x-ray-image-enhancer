# Project plan

The purpose of this application is to do image enhancing for X-ray images.

## Users

Users of this application are persons who want to test and perform image enhancing operations on X-ray images.

## Use cases

Use cases are described in the [use case documentation](../doc/use_cases.md).

- Enhance image

## Algorithms

Idea is to implement at least one image enhancing algorithm, called binning. 
Optionally, median filtering algorithm will be implemented.

At first, simple algorithm without multithreading is implemented. Algorithm can be optimized with concurrency.

### Binning

Method is described in the documentation about [binning](../doc/binning.md).

At sum of adjacent pixels for calculating combined pixel value will be implemented. 
Optionally, average, median, minimum, maximum of adjacent pixels could be implemented. 

### Median filtering (optional)

Median filtering is another technique for removing noise.

## Command-line interface (optional)

Simple command-line line interface can be implemented. 
User can give operation type and one or multiple image files to process.

Example commands:

`x-ray-image-enhancer-cli -binning 2x2 "hand.bmp"`

`x-ray-image-enhancer-cli -b 3x3 "image1.bmp" "image2.bmp"`

## User interface

Simple user interface for loading, viewing, enhancing and exporting images will be implemented. 
Before starting to implement UI, an interactive mockup is created based on the use cases. Actual UI will be done with Qt Quick. 

## Functional requirements

### Algorithms
- Read 8-bit grayscale bitmap image
- Perform 2x2 binning on the image
- Export 16-bit grayscale binned image
- Perform median filtering on the image (optional)

### Command-line interface
- Read image enhancing methods given as command-line parameters
- Read input image files given as command-line parameters
- Perform given enhancing operations for input images
 
### User interface
- Open image files
- Select images
- Perform enhancing operation for selected images
- Export enhanced images
- Undo enhancing operation for selected images (optional)

## Non-functional requirements
- Reliable
- Easy-to-use
- Responsive

## Architecture

Application architecture is described in the [architecture documentation](../doc/architecture.md).

## Development process

Development will be done using the process described below.

```mermaid
flowchart TD
  1([Understand domain]) --> 2
  2([Create project plan])--> 3
  3([Document domain])--> 4
  4([Write use cases])--> 5
  5([Create UI prototype])--> 6
  6([Plan architecture])--> 7
  7([Implement initial UI])--> 8
  8([Implement architecture])--> 9
  9([Write unit tests])--> 10
  10([Implement algorithms])--> 11
  11([Implement user stories])--> 12
  12([Refine UI])--> 13
  13([Test UI])--> 14([Finalize documentation])
```

## Testing

Algorithm development will be done with test-driven development (TDD) approach.

User interface will be tested manually.

## Tools

- Git (version control)
- GitHub (storing and managing code, project management)
- GitHub Desktop (working with GitHub)
- Visual Studio Code (markdown documentation)
- Inkscape (images for documentation)
- Adobe XD (user interface mockup)
- Qt Creator (IDE)
- CMake (build file generation)
- Valgrind (memory debugging and memory leak detection)

## Libraries

- Boost (unit testing)
- OpenCV (image processing, image reading and writing)
- Qt (user interface)

## Coding style

- C++17 standard
- C++ Core Guidelines (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)