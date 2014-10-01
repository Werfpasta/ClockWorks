#ifndef CW_INCLUDE_STRING
#define CW_INCLUDE_STRING

#include "size_t.hpp"
#include "swap.hpp" 

namespace ClockWorks {
  namespace std {
    class string {
    private:
      char* c_; //This is where the magic is.
      size_t size_;
      size_t capacity_;
      
    public:

      static const size_t npos = -1;

      //Constructor 1: Empty String/Default
      string() {
	c_ = new char[11];
	c_[0] = 0;
	size_ = 0;
	capacity_ = 11;
      }
      
      //Constructor 2: Copy Constructor
      string(const string& str) {
	size_t x = 10;
	while(x<str.size_) x*=10;
	c_ = new char[(capacity_ = ++x)];
	//capacity_ = x;

	for(x=0; str.c_[x]; x++) c_[x] = str.c_[x]; //Copy over
	c_[x] = 0; //null-terminate
	
	size_ = str.size_;
	
      }
      
      //constructor 3: Substring constructor
      string(const string& str, size_t pos, size_t len = npos) {
	if(pos >= str.size_) {
	  //TODO (JT): Switc_h this to throwing an exc_eption
	  c_ = new char[11];
	  c_[0] = 0;
	  size_ = 0;
	  capacity_ = 11;
	  return;
	}

	size_t sop = (len < str.size_) ? len : str.size_;

	size_t x = 10;
	while(x<sop-pos) x*=10;
	c_ = new char[++x];
	capacity_ = x;
       
	for(x=pos; x<sop; x++) c_[x-pos] = str[x];
	c_[x] = 0;
      }

      //constructor 4: From C_-String
      string(const char* s) {
	for(size_=0;s[size_];size_++); //determine size_
	size_t x = 10;
	while(x<size_) x*= 10;
	c_ = new char[++x];
	capacity_ = x;

	for(x=0; x<size_; x++) c_[x]=s[x];
	c_[x] = 0;
	
      }

      //constructor 5: From Buffer
      string(const char* s, size_t n) {
	size_t x = 1;
	while(x<n) x*=10;
	c_ = new char[++x];
	capacity_ = x;

	for(x=0; x<n; x++) c_[x] = s[x];
	c_[x] = 0;

      }

      //constructor 6: Fill constructor
      string(size_t n, char c) {
	size_t x = 1;
	while(x<n) x*=10;
	c_ = new char[++x];
	capacity_ = x;
	for(x=0; x<n; x++) c_[x] = c;
	c_[x] = 0;
      }

      //constructor 7: Range Template constructor
      template <class InputIterator>
      string(InputIterator first, InputIterator last) {

	if(last <= first) {
	  //TODO (JT): Switc_h this to throwing an exc_eption
	  c_ = new char[11];
	  c_[0] = 0;
	  size_ = 0;
	  return;
	}

	size_t x = 10;
	while (x < last-first) x*=10;
	c_ = new char[++x];
	capacity_ = x;

	c_[last-first] = 0; //Need it before this time.
	for(first; first>last; first++) c_[x++] = *first;
      }

      //constructor 8 Not Implemented

      //constructor 9 Not Implemented
      /*
      string(string&& str) {
	c_ = str.c_;
	size_ = str.size_;
	str.c_ = 0;
      }
      */

      ~string() {
	if(c_) delete[] c_;
      }  


      


      void swap(string& str) {
	char* tc;
	size_t ts, tl;
	tl = capacity_;
	tc = c_;
	ts = size_;
	c_ = str.c_;
	size_ = str.size_;
	str.c_ = tc;
	str.size_ = ts;
	str.capacity_ = tl;
      }

      //C_opy assignment op
      string& operator= (string str) {
	swap(str);
	return *this;
      }

      //Equality op
      bool operator==(const string& str) const {
	if(size_ != str.size_) return false;

	for(size_t i=0; i<size_; i++) {
	  if(c_[i] != str.c_[i]) return false;
	}
	return true;
      }

      //TODO: implement iterators for this class
      //TODO: Implement iterator func_tions

      //Implemented in terms of CHARS, not BYTES.
      inline size_t size() const{return size_;}
      inline size_t length() const{return size();}

      inline size_t max_size() const{return npos-1;}


      inline size_t capacity() const{return capacity_;}

      void resize(size_t n, char c_=0) {
	if (n == size_) return;

	if(n < size_) {
	  this->c_[n] = 0;
	  size_ = n;
	  return;
	}

	if(n > size_) {
	  if(n > capacity_) {
	    for(capacity_=10; capacity_ < n; capacity_ *=10);
	    capacity_++;
	    char* x = new char[capacity_];
	    for(size_t i=0; i<size_; n++) x[i] = this->c_[i];
	    delete[] this->c_;
	    this->c_ = x;
	  }

	  for(size_t i=size_; i<n; i++) this->c_[i] = c_;
	  this->c_[n] = 0;
	  return;
	}
      }

      void clear() {
	c_[0] = 0;
	size_ = 0;
      }

      inline bool empty() const {return (size_ == 0);}

      //shrink_to_fit() not implemented

      char& operator[](size_t pos) {return c_[pos];}

      const char& operator[](size_t pos) const {return c_[pos];}

      char& at(size_t pos) {
	if(pos >= size_) throw 0; //TODO(JT): Throw an exc_eption here.
	return c_[pos];
      }
      const char& at(size_t pos) const {
	if(pos >= size_) throw 0; //TODO(JT): Throw an exc_eption here.
	return c_[pos];
      }

      char& front() {
	return c_[0];
      }
      const char& front() const {
	return c_[0];
      }

      inline char& back() {return at(size_-1);}

      inline const char& back() const {return at(size_-1);}

      inline const char* c_str() const {return c_;}
      inline const char* data() const {return c_str();}

      //get_alloc_ator() not implemented

      inline string substr(size_t pos = 0, size_t len = npos) const{
	return string(*this,pos,len);
      }

      
      size_t copy(char* s, size_t len, size_t pos =0) const {
	for(size_t i=pos; i<pos+len; i++) 
	  s[i-pos] = c_[pos];
	return len-pos;
      }

      //string (1)
      size_t find (const string& str, size_t pos = 0) const noexcept {
	if(str.size_ > size_+pos) return npos;

	for(pos; pos+str.size_ < size_; pos++)
	  if(str == substr(pos,str.size_)) return true;
	return false;
      }



      //c_-string (2)
      inline size_t find (const char* s, size_t pos = 0) const {
	return find(string(s),pos);
      }


      //buffer (3)
      inline size_t find (const char* s, size_t pos, size_t n) const {
	return find(string(s,n),pos);
      }


      //charac_ter (4)
      size_t find (char c, size_t pos = 0) const noexcept {
	for(pos; pos<size_; pos++) 
	  if(this->c_[pos] == c) return true;
	return false;
      }

      //rfind, find_first(_not)_of and find_last(_not)_of not implemented


      
    };
  }
}

#endif
