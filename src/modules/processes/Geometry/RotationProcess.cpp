// ****************************************************************************
// PixInsight Class Library - PCL 02.00.13.0692
// Standard Geometry Process Module Version 01.01.00.0247
// ****************************************************************************
// RotationProcess.cpp - Released 2014/11/14 17:18:46 UTC
// ****************************************************************************
// This file is part of the standard Geometry PixInsight module.
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

#include "RotationProcess.h"
#include "RotationParameters.h"
#include "RotationInstance.h"
#include "RotationInterface.h"

namespace pcl
{

// ----------------------------------------------------------------------------

RotationProcess* TheRotationProcess = 0;

// ----------------------------------------------------------------------------

#include "RotationIcon.xpm"

// ----------------------------------------------------------------------------

RotationProcess::RotationProcess() : MetaProcess()
{
   TheRotationProcess = this;

   // Instantiate process parameters

   TheRotationAngleRotationParameter = new RotationAngle( this );
   TheOptimizeFastRotationsRotationParameter = new OptimizeFastRotations( this );
   TheInterpolationAlgorithmRotationParameter = new InterpolationAlgorithm( this );
   TheClampingThresholdRotationParameter = new ClampingThreshold( this );
   TheSmoothnessRotationParameter = new Smoothness( this );
   TheFillRedRotationParameter = new FillRed( this );
   TheFillGreenRotationParameter = new FillGreen( this );
   TheFillBlueRotationParameter = new FillBlue( this );
   TheFillAlphaRotationParameter = new FillAlpha( this );
}

// ----------------------------------------------------------------------------

IsoString RotationProcess::Id() const
{
   return "Rotation";
}

// ----------------------------------------------------------------------------

IsoString RotationProcess::Category() const
{
   return "Geometry";
}

// ----------------------------------------------------------------------------

uint32 RotationProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String RotationProcess::Description() const
{
   return "";
}

// ----------------------------------------------------------------------------

const char** RotationProcess::IconImageXPM() const
{
   return RotationIcon_XPM;
}

// ----------------------------------------------------------------------------

ProcessInterface* RotationProcess::DefaultInterface() const
{
   return TheRotationInterface;
}

// -------------------------------------------------------------------------

ProcessImplementation* RotationProcess::Create() const
{
   return new RotationInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* RotationProcess::Clone( const ProcessImplementation& p ) const
{
   const RotationInstance* instPtr = dynamic_cast<const RotationInstance*>( &p );
   return (instPtr != 0) ? new RotationInstance( *instPtr ) : 0;
}

// ----------------------------------------------------------------------------

} // pcl

// ****************************************************************************
// EOF RotationProcess.cpp - Released 2014/11/14 17:18:46 UTC
