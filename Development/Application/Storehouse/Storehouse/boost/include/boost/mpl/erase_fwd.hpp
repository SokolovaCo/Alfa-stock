
#ifndef BOOST_MPL_ERASE_FWD_HPP_INCLUDED
#define BOOST_MPL_ERASE_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: erase_fwd.hpp 49239 2008-10-10 09:10:26Z agurtovoy $
// $Date: 2008-10-10 13:10:26 +0400 (Пт, 10 окт 2008) $
// $Revision: 49239 $

namespace boost { namespace mpl {

template< typename Tag > struct erase_impl;
template< typename Sequence, typename First, typename Last > struct erase;

}}

#endif // BOOST_MPL_ERASE_FWD_HPP_INCLUDED