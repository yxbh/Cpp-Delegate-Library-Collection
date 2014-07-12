C++ Delegate Library Collection
===============================

This is a collection of C++ delegate libraries that I've discovered and collected so far.

## Library
Here's the current list of delegate libraries in this repo (2014/06):
 * FastFunc:  
   A C++11 re-implementation of Don Clugston's original FastDelegate([CodeProject link](http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)).  
   Signature: `ssvu::FastFunc`  

 * FastDelegate:  
   A C++11 variadic template version of Don Clugston's original FastDelegate([CodeProject link](http://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible)).
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
Boost unit test is also available under the unit_test directory. Both a VS2013 and a Qt project are provided. You will have to modify the Boost library paths to your own before you build the tests. VS solution is setted up to run the test post-build.

## Known Issues
### Visual Studio
 - VS2013 lacks support for constexpr and noexcept, VS build redefines the 2 keywords to nothing through preprocessor macro. These macros will be removed once the next version of VS comes out as the CTP already provides limited support for constexpr and full support for noexcept.
 - VS2013 lacks default move constructor and assignment operator. I've provided implementations. AFAIK this is also fixed in the comming VS release.

### SRDelegate
 - VS2013 lacks two phase template look-up. There appear to be some SFINAE related issues causing certain delegate constructions not compiling due to delegate::functor_stub not overloading correctly. Runtime delegate construction from function pointers that has non-void function parameter fails to compile on VS2013. The SFINAE failing part is just my own speculation, if anyone could help me make it work, then it'd much appreciated! Workaround: use the generic::from<> template functions (better performance anyway).

## License
Each library should be retained within the original license that they were distributed in. I do not claim credit for each library's original implementation, except for my own modification.

If you are the oringnal author of any of the libraries and you wish to change the license or remove the library from this repository. Please drop me a message or raise an issue in the tracker.
