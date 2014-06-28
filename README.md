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


## License
Each library should be retained within the original license that they were distributed in. I do not claim credit for each library's original implementation, except for my own modification.

If you are the oringnal author of any of the libraries and you wish to change the license or remove the library from this repository. Please drop me a message or raise an issue in the tracker.
