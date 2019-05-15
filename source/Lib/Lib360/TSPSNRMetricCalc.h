/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2018, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     TSPSNRMetricCalc.h
    \brief    SPSNRMetric class (header)
*/

#ifndef __TSPSNRCALC__
#define __TSPSNRCALC__
#include "TGeometry.h"

// ====================================================================================================================
// Class definition
// ====================================================================================================================

#if SVIDEO_SPSNR_NN

class TSPSNRMetric
{
private:
  Bool      m_bSPSNREnabled;
  Double    m_dSPSNR[3];
  
  CPos2D*   m_pCart2D;
  IPos2D*   m_fpTable;
#if SVIDEO_CHROMA_TYPES_SUPPORT
  IPos2D*   m_fpTableC;
#endif
  Int       m_iSphNumPoints;

  Int       m_outputBitDepth[MAX_NUM_CHANNEL_TYPE];         ///< bit-depth of output file
  Int       m_referenceBitDepth[MAX_NUM_CHANNEL_TYPE];      ///< bit-depth of reference file
#if SVIDEO_CF_SPSNR_NN
  TGeometry  *m_pcCodingGeometry;
  TGeometry  *m_pcRefGeometry;  

  SVideoInfo    m_refVideoInfo;
  SVideoInfo    m_codingVideoInfo;
  InputGeoParam m_geoParam;
#if SVIDEO_CF_SPSNR_NN_ENH
  SPos2D*       m_pSamplePosTable;
  SPos2D*       m_pSamplePosRecTable;
  SPos2D*       m_pSamplePosCTable;  
  SPos2D*       m_pSamplePosCRecTable;
#else
  IPos*       m_pSamplePosTable;
  IPos*       m_pSamplePosRecTable;
  IPos*       m_pSamplePosCTable;  
  IPos*       m_pSamplePosCRecTable;
#endif
#endif
public:
  TSPSNRMetric();
  virtual ~TSPSNRMetric();
  Bool    getSPSNREnabled()  { return m_bSPSNREnabled; }
  Void    setSPSNREnabledFlag(Bool bEnabledFlag)  { m_bSPSNREnabled = bEnabledFlag; }
  Void    setOutputBitDepth(Int iOutputBitDepth[MAX_NUM_CHANNEL_TYPE]);
  Void    setReferenceBitDepth(Int iReferenceBitDepth[MAX_NUM_CHANNEL_TYPE]);
  Double* getSPSNR() {return m_dSPSNR;}
  Void    sphSampoints(const std::string &cSphDataFile);
  Void    sphToCart(CPos2D*, CPos3D*);
  Void    createTable(TGeometry *pcCodingGeomtry);
  Void    xCalculateSPSNR( PelUnitBuf& cOrgPicYuv, PelUnitBuf& cPicD );
#if SVIDEO_CF_SPSNR_NN
  Void    initCFSPSNR(SVideoInfo& referenceVideoInfo, SVideoInfo& codingvideoInfo, InputGeoParam& sCodingParam);
  Void    createTableCFSPSNR(UInt uiXScale, UInt uiYScale);
  Void    xCalculateCFSPSNR( PelUnitBuf *pcOrigPicYuv, PelUnitBuf* pcRecPicYuv);
#endif

#if !SVIDEO_ROUND_FIX
  inline Int round(POSType t) { return (Int)(t+ (t>=0? 0.5 :-0.5)); }; 
#endif
};

#endif
#endif // __TSPSNRCALC
