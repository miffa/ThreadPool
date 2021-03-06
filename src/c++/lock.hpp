/*
 * lock.hpp
 *
 *
 * Lock Implementation
 *
 *
 * Copyright (C) 2012-2013  Bryant Moscon - bmoscon@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright,
 *    license and disclaimer information.
 *
 * 3. The end-user documentation included with the redistribution, if any, must 
 *    include the following acknowledgment: "This product includes software 
 *    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
 *    place and form as other third-party acknowledgments. Alternately, this 
 *    acknowledgment may appear in the software itself, in the same form and 
 *    location as other such third-party acknowledgments.
 *
 * 4. Except as contained in this notice, the name of the author, Bryant Moscon,
 *    shall not be used in advertising or otherwise to promote the sale, use or 
 *    other dealings in this Software without prior written authorization from 
 *    the author.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 */

#ifndef __LOCK__
#define __LOCK__

#include <pthread.h>
#include <cassert>

#include "lock_.hpp"


class Lock : Lock_ {
  
public:
  
  virtual int init(const LockTypes type = DEFAULT)
  {
    pthread_mutexattr_t mutex_attr;

    assert(pthread_mutexattr_init(&mutex_attr) == 0);

    if (type == RECURSIVE) {
      assert(pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE) == 0);
    } else {
      assert(pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_DEFAULT) == 0);
    }

    return pthread_mutex_init(&mutex_, &mutex_attr);
  }


  virtual int lock()
  {
    return (pthread_mutex_lock(&mutex_));
  }


  virtual int unlock()
  {
    return (pthread_mutex_unlock(&mutex_));
  }

  pthread_mutex_t *getMutex()
  {
    return (&mutex_);
  }
  

private:
  pthread_mutex_t mutex_;
  
};




#endif
