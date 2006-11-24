/*
  Copyright (C) 1999, 2002 Aladdin Enterprises.  All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  L. Peter Deutsch
  ghost@aladdin.com

 */
/* $Id: md5.h,v 1.4 2002/04/13 19:20:28 lpd Exp $ */
/*
  Independent implementation of MD5 (RFC 1321).

  This code implements the MD5 Algorithm defined in RFC 1321, whose
  text is available at
	http://www.ietf.org/rfc/rfc1321.txt
  The code is derived from the text of the RFC, including the test suite
  (section A.5) but excluding the rest of Appendix A.  It does not include
  any code or documentation that is identified in the RFC as being
  copyrighted.

  The original and principal author of md5.h is L. Peter Deutsch
  <ghost@aladdin.com>.  Other authors are noted in the change history
  that follows (in reverse chronological order):

  2002-04-13 lpd Removed support for non-ANSI compilers; removed
	references to Ghostscript; clarified derivation from RFC 1321;
	now handles byte order either statically or dynamically.
  1999-11-04 lpd Edited comments slightly for automatic TOC extraction.
  1999-10-18 lpd Fixed typo in header comment (ansi2knr rather than md5);
	added conditionalization for C++ compilation from Martin
	Purschke <purschke@bnl.gov>.
  1999-05-03 lpd Original version.
 */

#ifndef MD5_H__
#define MD5_H__

#include <string>

namespace gloox
{

  class MD5
  {
    public:
      /**
       *
       */
      MD5();

      /**
       * Virtual Destructor.
       */
      virtual ~MD5();

      /**
       *
       */
      void feed( const unsigned char *data, int bytes );

      /**
       *
       */
      void feed( const std::string& data );

      /**
       *
       */
      void finalize();

      /**
       *
       */
      const std::string hex();

      /**
       *
       */
      const std::string binary();

      /**
       *
       */
      void reset();

    private:
      struct MD5State
      {
          unsigned int count[2]; /* message length in bits, lsw first */
          unsigned int abcd[4]; /* digest buffer */
          unsigned char buf[64]; /* accumulate block */
      } m_state;

      void init();
      void process( const unsigned char *data );

      static const unsigned char pad[64];

      bool m_finished;

  };

}

#endif // MD5_H__
