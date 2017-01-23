C++ Delegate Library Collection
===============================

This is a collection of C++ delegate libraries that I've discovered and collected so far.

## Library
Here's the current list of delegate libraries in this repo (2014/06):
 * FastFunc:  
   A C++11 re-implementation of Don Clugston's original FastDelegate by Paúl Jiménez(Ceniza)([CodeProject link](http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible))
([Gist](https://gist.github.com/yxbh/997d5a7791e3fe18e94f)).
   Signature: `ssvu::FastFunc`  

 * FastDelegate:  
   A C++11 variadic template version of Don Clugston's original FastDelegate ([Source link](https://sites.google.com/site/ceniza666/cpp))
([Original Implementation CodeProject link](http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)).
  Signature: `fastdelegate::FastDelegate`

 * SRDelegate:  
   A C++11 re-implementation of Sergey Ryazanov's "The Impossibly Fast C++ Delegates"([CodeProject link](http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates)).  
   Signature: `generic::delegate`  


## Modification
These libraries also contain my own personal modifications which include:
 * bugfixes
 * new features
 * VC workarounds (e.g. C++11 non-conformance workarounds).

## Test
Unit tests using the Catch library are available to test how well the equality operators work. These are available under the unit_test directory. Both a VS2015 and a Qt project(outdated) are provided. VS solution is setted up to run the test post-build.

The project originally used Boost unit test which was a pain to add in all the dependencies and keeping it up to date. Catch is header only and just as easy to use.

## Known Issues
None AFAIK.

## Benchmark
A benchmark is available to do performance comparison of function call performance for the libraries. It measures the function call performance. The benchmark also contains the original FastDelegate written by Don Clugston.

Feel free to send in pull request and contribute.

### Test Cases
Function types tested at the moment are below:
 * static global function (with and without parameter)
 * static member function (with and without parameter)
 * non-virtual member function (with and without parameter)
 * inlined functions

### Build
A Qt project file is provided. It has been tested on a Win7 laptop and a Win8 desktop.

A Visual Studio 2015 solution is also provided. This is tested on a Win10 desktop.

Due to the fact that VC++ is still C++11 non-conformance, quite a bit of workaround had to be added to make the C++11 versions of the delegate libraries to work. What I've done is providing 2 copies of each of the affected libraries separated by #ifdef's within their respective header files. If the '_MSC_VER' is detected then the visual studio version containing the workarounds would be used.

In Visual Studio, COMDAT Folding needs to be disabled in the linker ('/OPT:ICF' -> '/OPT:NOICF') in order for the libraries to work correctly. In our scenario, COMDAT Folding simply make the comparison operators work incorrectly. If you need equality operators in your delegates, you will have to disable it in your VS projects too.

## License
Each library should be retained within the original license that they were distributed in. I do not claim credit for each library's original implementation, except for my own modification.

If you are the oringnal author of any of the libraries and you wish to change the license or remove the library from this repository. Please drop me a message or raise an issue in the tracker.
