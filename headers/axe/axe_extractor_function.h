//-----------------------------------------------------------------------------
//  Original Author: Gene Bushuyev
//  Copyright (C) 2011 GB Research, LLC
//  
//  Boost Software License - Version 1.0 - August 17th, 2003
//
//  Permission is hereby granted, free of charge, to any person or organization
//  obtaining a copy of the software and accompanying documentation covered by
//  this license (the "Software") to use, reproduce, display, distribute,
//  execute, and transmit the Software, and to prepare derivative works of the
//  Software, and to permit third-parties to whom the Software is furnished to
//  do so, all subject to the following:
//
//  The copyright notices in the Software and this entire statement, including
//  the above license grant, this restriction and the following disclaimer,
//  must be included in all copies of the Software, in whole or in part, and
//  all derivative works of the Software, unless such copies or derivative
//  works are solely in the form of machine-executable object code generated by
//  a source language processor.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//  FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef AXE_EXTRACTOR_FUNCTION_H
#define AXE_EXTRACTOR_FUNCTION_H

#include <utility>
#include "axe_extractor.h"
#include "axe_trait.h"

namespace axe {

    //-------------------------------------------------------------------------
    // extractor operators and functions
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    template<class R, class E>
    r_extractor_t<
        typename std::enable_if<is_rule<typename std::remove_reference<R>::type>::value, R>::type,
        typename std::enable_if<is_extractor<typename std::remove_reference<E>::type>::value, E>::type
    >
    operator >> (R&& r, E&& e) 
    { 
        return r_extractor_t<R, E>(std::forward<R>(r), std::forward<E>(e));
    }

    //-------------------------------------------------------------------------
    template<class R, class T>
    r_extractor_t<
        typename std::enable_if<is_rule<typename std::remove_reference<R>::type>::value, R>::type,
        typename std::enable_if<!is_extractor<typename std::remove_reference<T>::type>::value, e_value_t<T>>::type
    >
    operator >> (R&& r, T& t) 
    { 
        return r_extractor_t<R, e_value_t<T>>(std::forward<R>(r), e_value_t<T>(t));
    }

    //-------------------------------------------------------------------------
    template<class E>
    e_ref_t<E>
    e_ref(E&& e) { return e_ref_t<E>(std::forward<E>(e)); }

    //-------------------------------------------------------------------------
    template<class T>
    e_length_t<T> e_length(T& t) { return e_length_t<T>(t); }

    //-------------------------------------------------------------------------
    template<class C>
    e_push_back_t<C> e_push_back(C& c) { return e_push_back_t<C>(c); }
}

#endif
