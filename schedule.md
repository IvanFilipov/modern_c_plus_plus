## Week 1

### Advanced OOP

recap:
- resource managment
- RAII
- special member functions and their rules (G4)

new:
- lvalue and rvalue
- RVO
- move semantics
- smart pointers
- initializing objects, initialize-list 

## Week 2

### Syntax sugers, templates and lambdas

recap:
- some special key words ( default, delete ( in classes ), final, override ... )
- c++ sytle cast and their use cases
- strings, stringstreams

new:
- type deduction ( auto, decltype )
- more about templates, variadic templates
- template metaprogramming
- constexpr
- lambda functions

## Week 3

### GIT + STL

tools: 
- git + some GUI + GitHub

recap:
- data structures learnt during DSA
- iterators
- different loops

new:
- STL basic data structures and their representations
- sequence containers:
    - std::array, std::vector, std::deque, std::list, std::forward_list
- container adaptors:
    - std::queue, std::stack, std::priority_queue
- usage and some algorithms
## Week 4

### Advanced data structures

recap:
- trees, blanaced trees
- hash functions, hash tables

new :
- n-tuples:
    - std::pair, std::tuple, std::tie
- associative containers:
    - std::set, std::map, std::unordered_set, std::unordered_map
- thier _multi_ versions : std::multimap, std::multiset, std::unordered_multiset, std::unordered_multimap
- overview of *\<algorithm\>*
- regular expressions:
    - std::regex

## Week 5

### Full standards covarage
_around 3 hours_
* some more stuff from C++14
* new things from C++17
* libraries and API design
* error handling
* maybe a bit more for advanced data structures...

## Week 6
_around 5 hours_
### System programming and multithreading

* from power ON to system starting (booting process)
  - BIOS/UEFI
  - bootloader
* a little bit about architectures:
  - motherboard, busses
  - CPU insides -> cores, caches, instructions
  - memory
* brief discusion about OS-es:
  - what they do?
  - kernel
  - rings
  - processes
  - system calls (a bit \*NIX stuff)
  - shell
* POSIX
* multithreading:
  - Concurrency vs Parallelism
  - synchronization primitives
  - green threads(fibers). Compare with other languages.
  - some code examples with different API's:
  POSIX (pthreads), C11, C++11
  - thread pool 
  - Asynchronous programming
  - classical concurrency problems
  - C++17 parallel struct/algo

## Week 7
_around 3 hours_
### Networks and network programming
* network basics: 
  - physical devices 
  - OSI model, protocols, TCP/IP stack 
* how the web is working (local network, NAT, ...)
* client-server model
* Berkeley sockets - C example
* Web communication protocols (Application level) 
- TODO: more details


## Week 8
_around 5 hours_
### Full applications (examples)
 * DB basics
 * example with HTTP server in C++, talking with DB and Web UI
 * example with openCV - creating an real time video chat
 * example with SDL



