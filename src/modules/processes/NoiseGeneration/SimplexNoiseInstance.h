// ****************************************************************************
// PixInsight Class Library - PCL 02.00.13.0689
// Standard NoiseGeneration Process Module Version 01.00.02.0206
// ****************************************************************************
// SimplexNoiseInstance.h - Released 2014/11/06 17:11:45 UTC
// ****************************************************************************
// This file is part of the standard NoiseGeneration PixInsight module.
//
// Copyright (c) 2003-2014, Pleiades Astrophoto S.L. All Rights Reserved.
//
// Redistribution and use in both source and binary forms, with or without
// modification, is permitted provided that the following conditions are met:
//
// 1. All redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. All redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the names "PixInsight" and "Pleiades Astrophoto", nor the names
//    of their contributors, may be used to endorse or promote products derived
//    from this software without specific prior written permission. For written
//    permission, please contact info@pixinsight.com.
//
// 4. All products derived from this software, in any form whatsoever, must
//    reproduce the following acknowledgment in the end-user documentation
//    and/or other materials provided with the product:
//
//    "This product is based on software from the PixInsight project, developed
//    by Pleiades Astrophoto and its contributors (http://pixinsight.com/)."
//
//    Alternatively, if that is where third-party acknowledgments normally
//    appear, this acknowledgment must be reproduced in the product itself.
//
// THIS SOFTWARE IS PROVIDED BY PLEIADES ASTROPHOTO AND ITS CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PLEIADES ASTROPHOTO OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, BUSINESS
// INTERRUPTION; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; AND LOSS OF USE,
// DATA OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ****************************************************************************

#ifndef __SimplexNoiseInstance_h
#define __SimplexNoiseInstance_h

#include <pcl/ProcessImplementation.h>

#include "SimplexNoiseParameters.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class SimplexNoiseInstance : public ProcessImplementation
{
public:

   SimplexNoiseInstance( const MetaProcess* );
   SimplexNoiseInstance( const SimplexNoiseInstance& );

   virtual void Assign( const ProcessImplementation& );
   virtual bool CanExecuteOn( const View&, pcl::String& whyNot ) const;
   virtual bool ExecuteOn( View& );
   virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/ );

private:

   float    p_amount;
   int32    p_scale;
   int32    p_offsetX;
   int32    p_offsetY;
   pcl_enum p_operator;

   friend class SimplexNoiseEngine;
   friend class SimplexNoiseInterface;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __SimplexNoiseInstance_h

// ****************************************************************************
// EOF SimplexNoiseInstance.h - Released 2014/11/06 17:11:45 UTC
