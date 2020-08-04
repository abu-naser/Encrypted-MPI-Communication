/* Copyright (c) 2001-2018, The Ohio State University. All rights
 * reserved.
 *
 * This file is part of the MVAPICH2 software package developed by the
 * team members of The Ohio State University's Network-Based Computing
 * Laboratory (NBCL), headed by Professor Dhabaleswar K. (DK) Panda.
 *
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level MVAPICH2 directory.
 *
 */

#include <regex.h>
#include "common_tuning.h"
#include "reduce_tuning.h"
#include "tuning/reduce_arch_tuning.h"
#include "mv2_arch_hca_detect.h"


int mv2_size_reduce_tuning_table = 0;
mv2_reduce_tuning_table *mv2_reduce_thresholds_table = NULL;

int *mv2_reduce_indexed_table_ppn_conf = NULL;
int mv2_reduce_indexed_num_ppn_conf = 1;
int *mv2_size_reduce_indexed_tuning_table = NULL;
mv2_reduce_indexed_tuning_table **mv2_reduce_indexed_thresholds_table = NULL;

int MV2_set_reduce_tuning_table(int heterogeneity)
{
  if (mv2_use_indexed_tuning || mv2_use_indexed_reduce_tuning) {
    int agg_table_sum = 0;
    int i;
    mv2_reduce_indexed_tuning_table **table_ptrs = NULL;
#ifndef CHANNEL_PSM
#ifdef CHANNEL_MRAIL_GEN2
    if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_X5650_12, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /* Lonestar Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_X5650_12__MLX_CX_QDR__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 3;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_X5650_12__MLX_CX_QDR__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 12;
      mv2_size_reduce_indexed_tuning_table[2] = 6;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_12ppn[] =
	GEN2__INTEL_XEON_X5650_12__MLX_CX_QDR__12PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_12ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    if ((MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
                 MV2_ARCH_INTEL_XEON_E5_2690_V2_2S_20, MV2_HCA_MLX_CX_CONNIB) ||
        MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
                 MV2_ARCH_INTEL_XEON_E5_2680_V2_2S_20, MV2_HCA_MLX_CX_CONNIB)) && !heterogeneity) {
      /* PSG Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 3;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2690_V2_2S_20__MLX_CX_CONNIB__1PPN;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2690_V2_2S_20__MLX_CX_CONNIB__2PPN;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 20;
      mv2_size_reduce_indexed_tuning_table[2] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_20ppn[] =
	GEN2__INTEL_XEON_E5_2690_V2_2S_20__MLX_CX_CONNIB__20PPN;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_20ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_E5_2630_V2_2S_12, MV2_HCA_MLX_CX_CONNIB) && !heterogeneity) {
      /* Wilkes Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 6;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2630_V2_2S_12__MLX_CX_CONNIB__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 6;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2630_V2_2S_12__MLX_CX_CONNIB__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 12;
      mv2_size_reduce_indexed_tuning_table[2] = 6;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_12ppn[] =
	GEN2__INTEL_XEON_E5_2630_V2_2S_12__MLX_CX_CONNIB__12PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_12ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_AMD_OPTERON_6136_32, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /*Trestles Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__AMD_OPTERON_6136_32__MLX_CX_QDR__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 3;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__AMD_OPTERON_6136_32__MLX_CX_QDR__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 32;
#if defined(_SMP_CMA_)
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_32ppn[] =
        GEN2_CMA__AMD_OPTERON_6136_32__MLX_CX_QDR__32PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_32ppn[] =
        GEN2__AMD_OPTERON_6136_32__MLX_CX_QDR__32PPN;
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 4;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_32ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 4;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_32ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_32ppn[] =
	GEN2__AMD_OPTERON_6136_32__MLX_CX_QDR__32PPN;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_32ppn;
#endif

      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				  MV2_ARCH_INTEL_XEON_E5_2670_16, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /*Gordon Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2670_16__MLX_CX_QDR__1PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2670_16__MLX_CX_QDR__1PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 6;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 6;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[0] = 6;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2670_16__MLX_CX_QDR__2PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2670_16__MLX_CX_QDR__2PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[1] = 7;
	table_ptrs[1] = mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[1] = 7;
	table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[1] = 7;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2670_16__MLX_CX_QDR__16PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
        GEN2__INTEL_XEON_E5_2670_16__MLX_CX_QDR__16PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 7;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 7;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 7;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
#endif
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				  MV2_ARCH_INTEL_XEON_E5_2670_16, MV2_HCA_MLX_CX_FDR) && !heterogeneity) {
      /*Yellowstone Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2670_16__MLX_CX_FDR__1PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2670_16__MLX_CX_FDR__1PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 3;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 2;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[0] = 2;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2670_16__MLX_CX_FDR__2PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2670_16__MLX_CX_FDR__2PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[1] = 3;
	table_ptrs[1] = mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[1] = 2;
	table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[1] = 2;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2670_16__MLX_CX_FDR__16PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
        GEN2__INTEL_XEON_E5_2670_16__MLX_CX_FDR__16PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 4;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 3;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 3;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
#endif
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				  MV2_ARCH_INTEL_XEON_E5_2680_16, MV2_HCA_MLX_CX_FDR) && !heterogeneity) {
      /*Stampede Table*/
      mv2_reduce_indexed_num_ppn_conf = 4;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[0] = 5;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[1] = 6;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[2] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_4ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__4PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_4ppn[] =
        GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__4PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 1;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_4ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 1;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_4ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 1;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_4ppn;
#endif

      mv2_reduce_indexed_table_ppn_conf[3] = 16;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
        GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[3] = 9;
	table_ptrs[3] = mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[3] = 6;
	table_ptrs[3] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[3] = 6;
      table_ptrs[3] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
#endif
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }

    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
		MV2_ARCH_INTEL_XEON_E5_2680_V4_2S_28, MV2_HCA_MLX_CX_EDR) && !heterogeneity) {
      /*RI2 Table*/
force_default_tables:
      MV2_COLL_TUNING_START_TABLE  (reduce, 6)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  5, GEN2__RI2__1PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 1,  5, GEN2_CMA__RI2__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  5, GEN2__RI2__2PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 2,  5, GEN2_CMA__RI2__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  5, GEN2__RI2__4PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 4,  5, GEN2_CMA__RI2__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  5, GEN2__RI2__8PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 8,  5, GEN2_CMA__RI2__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16, 5, GEN2__RI2__16PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 16, 5, GEN2_CMA__RI2__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 28, 6, GEN2__RI2__28PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 28, 6, GEN2_CMA__RI2__28PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				    MV2_ARCH_ARM_CAVIUM_V8, MV2_HCA_MLX_CX_FDR) && !heterogeneity) {
      /* ARM system at Hartree Center */
      MV2_COLL_TUNING_START_TABLE  (reduce, 5)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  2, GEN2_CMA__ARM_CAVIUM_V8_MLX_CX_FDR__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  3, GEN2_CMA__ARM_CAVIUM_V8_MLX_CX_FDR__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  3, GEN2_CMA__ARM_CAVIUM_V8_MLX_CX_FDR__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16,  3, GEN2_CMA__ARM_CAVIUM_V8_MLX_CX_FDR__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 24,  3, GEN2_CMA__ARM_CAVIUM_V8_MLX_CX_FDR__24PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				    MV2_ARCH_IBM_POWER8, MV2_HCA_MLX_CX_EDR) && !heterogeneity) {
      /* Ray Table */
      int pg_size = MPIDI_PG_Get_size(MPIDI_Process.my_pg);
      if (pg_size > 64) goto force_default_tables;

      MV2_COLL_TUNING_START_TABLE  (reduce, 3)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  5, GEN2_CMA__IBM_POWER8_MLX_CX_EDR__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  2, GEN2_CMA__IBM_POWER8_MLX_CX_EDR__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  2, GEN2_CMA__IBM_POWER8_MLX_CX_EDR__8PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				    MV2_ARCH_IBM_POWER9, MV2_HCA_MLX_CX_EDR) && !heterogeneity) {
      /* Sierra Table: Use table for Ray temporarily */
      int pg_size = MPIDI_PG_Get_size(MPIDI_Process.my_pg);
      if (pg_size > 64) goto force_default_tables;

      MV2_COLL_TUNING_START_TABLE  (reduce, 8)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  4, GEN2__IBM_POWER9_MLX_CX_EDR__1PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 1,  4, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  5, GEN2__IBM_POWER9_MLX_CX_EDR__2PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 2,  5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  5, GEN2__IBM_POWER9_MLX_CX_EDR__4PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 4,  5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  5, GEN2__IBM_POWER9_MLX_CX_EDR__8PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 8,  5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16, 5, GEN2__IBM_POWER9_MLX_CX_EDR__16PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 16, 5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 22, 5, GEN2__IBM_POWER9_MLX_CX_EDR__22PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 22, 5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__22PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 32, 5, GEN2__IBM_POWER9_MLX_CX_EDR__32PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 32, 5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__32PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 44, 5, GEN2__IBM_POWER9_MLX_CX_EDR__44PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 44, 5, GEN2_CMA__IBM_POWER9_MLX_CX_EDR__44PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_E5630_8, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /*RI Table*/
      MV2_COLL_TUNING_START_TABLE  (reduce, 4)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  6, GEN2__RI__1PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 1,  6, GEN2_CMA__RI__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  7, GEN2__RI__2PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 2,  7, GEN2_CMA__RI__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  1, GEN2__RI__4PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 4,  1, GEN2_CMA__RI__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  8, GEN2__RI__8PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 8,  8, GEN2_CMA__RI__8PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_E5_2680_V3_2S_24, MV2_HCA_MLX_CX_FDR) && !heterogeneity) {
      /*Comet Table*/
      mv2_reduce_indexed_num_ppn_conf = 1;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 24;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_24ppn[] =
	  GEN2__INTEL_XEON_E5_2680_24__MLX_CX_FDR__24PPN;
      /*
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_24ppn[] =
	  GEN2_CMA__INTEL_XEON_E5_2680_24__MLX_CX_FDR__24PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 6;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_24ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 6;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_24ppn;
      }
#else
      */
      mv2_size_reduce_indexed_tuning_table[0] = 6;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_24ppn;
      /*
#endif
      */
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }

    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
		MV2_ARCH_ANY, MV2_HCA_MLX_CX_EDR) && !heterogeneity) {
      /*RI2 Table*/
      MV2_COLL_TUNING_START_TABLE  (reduce, 3)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  4, GEN2__RI2__1PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 1,  4, GEN2_CMA__RI2__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  5, GEN2__RI2__2PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 2,  5, GEN2_CMA__RI2__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 28, 4, GEN2__RI2__28PPN)
      MV2_COLL_TUNING_ADD_CONF_CMA (reduce, 28, 4, GEN2_CMA__RI2__28PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else {
      /*Stampede Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[0] = 5;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[1] = 6;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
        GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 9;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 6;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 6;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
#endif
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
#elif defined (CHANNEL_NEMESIS_IB)
    if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				  MV2_ARCH_INTEL_XEON_E5_2680_16, MV2_HCA_MLX_CX_FDR) && !heterogeneity) {
      /*Stampede Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 5;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	NEMESIS__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 5;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	NEMESIS__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_size_reduce_indexed_tuning_table[2] = 7;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
	NEMESIS__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				  MV2_ARCH_INTEL_XEON_E5_2670_16, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /*Gordon Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	NEMESIS__INTEL_XEON_E5_2670_16__MLX_CX_QDR_1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	NEMESIS__INTEL_XEON_E5_2670_16__MLX_CX_QDR_2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_size_reduce_indexed_tuning_table[2] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
	NEMESIS__INTEL_XEON_E5_2670_16__MLX_CX_QDR_16PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				  MV2_ARCH_INTEL_XEON_E5_2670_16, MV2_HCA_MLX_CX_FDR) && !heterogeneity) {
      /*Yellowstone Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	NEMESIS__INTEL_XEON_E5_2670_16__MLX_CX_FDR__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	NEMESIS__INTEL_XEON_E5_2670_16__MLX_CX_FDR__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_size_reduce_indexed_tuning_table[2] = 3;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
	NEMESIS__INTEL_XEON_E5_2670_16__MLX_CX_FDR__16PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_AMD_OPTERON_6136_32, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /*Trestles Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 4;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	NEMESIS__AMD_OPTERON_6136_32__MLX_CX_QDR__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 3;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	NEMESIS__AMD_OPTERON_6136_32__MLX_CX_QDR__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      
      mv2_reduce_indexed_table_ppn_conf[2] = 32;
      mv2_size_reduce_indexed_tuning_table[2] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_32ppn[] =
	NEMESIS__AMD_OPTERON_6136_32__MLX_CX_QDR__32PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_32ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_E5630_8, MV2_HCA_MLX_CX_QDR) && !heterogeneity) {
      /*RI Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
        = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
                      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
                               * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
                                                         mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));

      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
        NEMESIS__RI__1PPN
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;

      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_size_reduce_indexed_tuning_table[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
        NEMESIS__RI__2PPN
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;

      mv2_reduce_indexed_table_ppn_conf[2] = 8;
      mv2_size_reduce_indexed_tuning_table[2] = 8;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_8ppn[] =
        NEMESIS__RI__8PPN
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_8ppn;

      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
        agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
        MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
                  (sizeof(mv2_reduce_indexed_tuning_table)
                   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
        mv2_reduce_indexed_thresholds_table[i] =
          mv2_reduce_indexed_thresholds_table[i - 1]
          + mv2_size_reduce_indexed_tuning_table[i - 1];
        MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
                    (sizeof(mv2_reduce_indexed_tuning_table)
                     * mv2_size_reduce_indexed_tuning_table[i]));
	}
      MPIU_Free(table_ptrs);
      return 0;
    }
    else {
      /*Stampede Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[0] = 5;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[1] = 6;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
        GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 6;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 6;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 6;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
#endif
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
#endif
#else /* !CHANNEL_PSM */
    if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_X5650_12, MV2_HCA_QLGIC_QIB) && !heterogeneity) {
      /*Sierra Table*/
      mv2_reduce_indexed_num_ppn_conf = 2;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_size_reduce_indexed_tuning_table[0] = 5;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	PSM__INTEL_XEON_X5650_12__MV2_HCA_QLGIC_QIB__1PPN;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      
      mv2_reduce_indexed_table_ppn_conf[1] = 12;
      mv2_size_reduce_indexed_tuning_table[1] = 6;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_12ppn[] =
	PSM__INTEL_XEON_X5650_12__MV2_HCA_QLGIC_QIB__12PPN;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_12ppn;
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_E5_2695_V3_2S_28, MV2_HCA_INTEL_HFI1) && !heterogeneity) {
      /*Bridges Table*/
      MV2_COLL_TUNING_START_TABLE  (reduce, 6)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  4, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 28,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__28PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_E5_2695_V4_2S_36, MV2_HCA_INTEL_HFI1) && !heterogeneity) {
      /* Bebop/Jade/Opal Table */
      MV2_COLL_TUNING_START_TABLE  (reduce, 5)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  5, PSM__INTEL_XEON_E5_2695_V4_2S_36_INTEL_HFI_100__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  5, PSM__INTEL_XEON_E5_2695_V4_2S_36_INTEL_HFI_100__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  5, PSM__INTEL_XEON_E5_2695_V4_2S_36_INTEL_HFI_100__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16,  5, PSM__INTEL_XEON_E5_2695_V4_2S_36_INTEL_HFI_100__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 36, 5, PSM__INTEL_XEON_E5_2695_V4_2S_36_INTEL_HFI_100__36PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			     MV2_ARCH_INTEL_XEON_PHI_7250, MV2_HCA_INTEL_HFI1) && !heterogeneity) {
      /* TACC-KNL Table */
      MV2_COLL_TUNING_START_TABLE  (reduce, 6)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  5, PSM__INTEL_XEON_PHI_7250_68_INTEL_HFI_100__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  6, PSM__INTEL_XEON_PHI_7250_68_INTEL_HFI_100__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  5, PSM__INTEL_XEON_PHI_7250_68_INTEL_HFI_100__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16, 5, PSM__INTEL_XEON_PHI_7250_68_INTEL_HFI_100__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 32, 5, PSM__INTEL_XEON_PHI_7250_68_INTEL_HFI_100__32PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 64, 4, PSM__INTEL_XEON_PHI_7250_68_INTEL_HFI_100__64PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
                             MV2_ARCH_INTEL_PLATINUM_8170_2S_52, MV2_HCA_INTEL_HFI1) && !heterogeneity) {
      /* Diamond-Skylake Table */
      MV2_COLL_TUNING_START_TABLE  (reduce, 7)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  3, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  4, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  4, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  4, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16, 4, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 26, 4, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__26PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 52, 4, PSM__INTEL_PLATINUM_8170_2S_52_INTEL_HFI_100__52PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
    else {
      /*default psm table: Bridges Table*/
      MV2_COLL_TUNING_START_TABLE  (reduce, 6)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 1,  4, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__1PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 2,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__2PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 4,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__4PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 8,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__8PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 16,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__16PPN)
      MV2_COLL_TUNING_ADD_CONF     (reduce, 28,  5, PSM__INTEL_XEON_E5_2695_V3_2S_28_INTEL_HFI_100__28PPN)
      MV2_COLL_TUNING_FINISH_TABLE (reduce)
    }
#endif /* !CHANNEL_PSM */
    {
      /*Stampede Table*/
      mv2_reduce_indexed_num_ppn_conf = 3;
      mv2_reduce_indexed_thresholds_table
	= MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
		      * mv2_reduce_indexed_num_ppn_conf);
      table_ptrs = MPIU_Malloc(sizeof(mv2_reduce_indexed_tuning_table *)
			       * mv2_reduce_indexed_num_ppn_conf);
      mv2_size_reduce_indexed_tuning_table = MPIU_Malloc(sizeof(int) *
							 mv2_reduce_indexed_num_ppn_conf);
      mv2_reduce_indexed_table_ppn_conf = MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
      
      mv2_reduce_indexed_table_ppn_conf[0] = 1;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_1ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
#if defined(_SMP_CMA_)
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__1PPN;
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_cma_reduce_indexed_thresholds_table_1ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[0] = 5;
	table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[0] = 5;
      table_ptrs[0] = mv2_tmp_reduce_indexed_thresholds_table_1ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[1] = 2;
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_2ppn[] =
	GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
#if defined(_SMP_CMA_)
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn[] =
	GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__2PPN;
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_cma_reduce_indexed_thresholds_table_2ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[1] = 6;
	table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[1] = 6;
      table_ptrs[1] = mv2_tmp_reduce_indexed_thresholds_table_2ppn;
#endif
      
      mv2_reduce_indexed_table_ppn_conf[2] = 16;
#if defined(_SMP_CMA_)
      mv2_reduce_indexed_tuning_table mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn[] =
        GEN2_CMA__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
#endif
      mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table_16ppn[] =
        GEN2__INTEL_XEON_E5_2680_16__MLX_CX_FDR__16PPN;
#if defined(_SMP_CMA_)
      if (g_smp_use_cma) {
	mv2_size_reduce_indexed_tuning_table[2] = 6;
	table_ptrs[2] = mv2_tmp_cma_reduce_indexed_thresholds_table_16ppn;
      }
      else {
	mv2_size_reduce_indexed_tuning_table[2] = 6;
	table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
      }
#else
      mv2_size_reduce_indexed_tuning_table[2] = 6;
      table_ptrs[2] = mv2_tmp_reduce_indexed_thresholds_table_16ppn;
#endif
      
      agg_table_sum = 0;
      for (i = 0; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	agg_table_sum += mv2_size_reduce_indexed_tuning_table[i];
      }
      mv2_reduce_indexed_thresholds_table[0] =
	MPIU_Malloc(agg_table_sum * sizeof (mv2_reduce_indexed_tuning_table));
      MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], table_ptrs[0],
		  (sizeof(mv2_reduce_indexed_tuning_table)
		   * mv2_size_reduce_indexed_tuning_table[0]));
      for (i = 1; i < mv2_reduce_indexed_num_ppn_conf; i++) {
	mv2_reduce_indexed_thresholds_table[i] =
	  mv2_reduce_indexed_thresholds_table[i - 1]
	  + mv2_size_reduce_indexed_tuning_table[i - 1];
	MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[i], table_ptrs[i],
		    (sizeof(mv2_reduce_indexed_tuning_table)
		     * mv2_size_reduce_indexed_tuning_table[i]));
      }
      MPIU_Free(table_ptrs);
      return 0;
    }
  }
    else {
#ifndef CHANNEL_PSM
#ifdef CHANNEL_MRAIL_GEN2
      if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
			       MV2_ARCH_INTEL_XEON_X5650_12, MV2_HCA_MLX_CX_QDR) && !heterogeneity){
        mv2_size_reduce_tuning_table = 6;
        mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
                                                  sizeof (mv2_reduce_tuning_table));
        mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
	  {
	    12,
	    4,
	    4,
	    {1, 1, 0, 0},
	    4,
	    {
	      {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {4096, 32768, &MPIR_Reduce_binomial_MV2},
	      {32768, 262144,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {4096, 32768, &MPIR_Reduce_binomial_MV2},
	    },
	    2,
	    {
	      {0, 4096, &MPIR_Reduce_shmem_MV2},
	      {4096, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    24,
	    4,
	    4,
	    {1, 1, 1, 0},
	    4,
	    {
	      {0, -1, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {0, 262144, &MPIR_Reduce_redscat_gather_MV2},
	      {262144, 1048576, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    2,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    48,
	    4,
	    4,
	    {1, 1, 1, 0},
	    4,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 131072,  &MPIR_Reduce_binomial_MV2},
	      {131072, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    2,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    96,
	    4,
	    4,
	    {1, 1, 1, 0},
	    4,
	    {
	      {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {4096, 16384,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    2,
	    {
	      {0, 4096, &MPIR_Reduce_shmem_MV2},
	      {4096, -1,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
	    },
	  },
	  {
	    192,
	    4,
	    4,
	    {1, 1, 1, 0},
	    4,
	    {
	      {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    2,
	    {
	      {0, 4096, &MPIR_Reduce_shmem_MV2},
	      {16384, -1, &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    384,
	    4,
	    4,
	    {1, 1, 1, 1, 0},
	    5,
	    {
	      {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {4096, 8192,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 65536,&MPIR_Reduce_binomial_MV2},
	      {65536, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    3,
	    {
	      {0, 4096, &MPIR_Reduce_shmem_MV2},
	      {4096, 8192, &MPIR_Reduce_binomial_MV2},
	      {16384, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
        }; 
        MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
		    mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table));
	return 0;
      } else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				      MV2_ARCH_INTEL_XEON_E5_2680_16, MV2_HCA_MLX_CX_FDR) && !heterogeneity){
        /*Stampede*/
        mv2_size_reduce_tuning_table = 8;
        mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
                                                  sizeof (mv2_reduce_tuning_table));
        mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
	  {
	    16,
	    4,
	    4,
	    {1, 0, 0},
	    3,
	    {
	      {0, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {262144, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    2,
	    {
	      {0, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536,-1,  &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    32,
	    4,
	    4,
	    {1, 1, 1, 1, 0, 0, 0},
	    7,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 32768, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {32768, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {262144, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    6,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {16384, 32768, &MPIR_Reduce_shmem_MV2},
	      {32768, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536, 262144, &MPIR_Reduce_shmem_MV2},
	      {262144,-1,  &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    64,
	    4,
	    4,
	    {1, 1, 1, 1, 0},
	    5,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {262144, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    5,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {262144, -1, &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    128,
	    4,
	    4,
	    {1, 0, 1, 0, 1, 0},
	    6,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {262144, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    5,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {262144, -1, &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    256,
	    4,
	    4,
	    {1, 1, 1, 0, 1, 1, 0},
	    7,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 32768, &MPIR_Reduce_binomial_MV2},
	      {32768, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 262144, &MPIR_Reduce_binomial_MV2},
	      {262144, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    6,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {16384, 32768, &MPIR_Reduce_shmem_MV2},
	      {32768, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {262144, -1, &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    512,
	    4,
	    4,
	    {1, 0, 1, 1, 1, 0},
	    6,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 262144, &MPIR_Reduce_binomial_MV2},
	      {262144, 1048576, &MPIR_Reduce_binomial_MV2},
	      {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    5,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {262144, -1, &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    1024,
	    4,
	    4,
	    {1, 0, 1, 1, 1},
	    5,
	    {
	      {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 262144, &MPIR_Reduce_binomial_MV2},
	      {262144, -1, &MPIR_Reduce_binomial_MV2},
	    },
	    5,
	    {
	      {0, 8192, &MPIR_Reduce_shmem_MV2},
	      {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {16384, 65536, &MPIR_Reduce_shmem_MV2},
	      {65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {262144, -1, &MPIR_Reduce_binomial_MV2},
	    },
	  },
	  {
	    2048,
	    4,
	    4,
	    {1, 0, 1, 1, 1,1},
	    6,
	    {
	      {0, 2048, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {2048, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {4096, 16384, &MPIR_Reduce_binomial_MV2},
	      {16384, 65536, &MPIR_Reduce_binomial_MV2},
	      {65536, 131072, &MPIR_Reduce_binomial_MV2},
	      {131072, -1, &MPIR_Reduce_binomial_MV2},
	    },
	    6,
	    {
	      {0, 2048, &MPIR_Reduce_shmem_MV2},
	      {2048, 4096, &MPIR_Reduce_shmem_MV2},
	      {4096, 16384, &MPIR_Reduce_shmem_MV2},
	      {16384, 65536, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {65536, 131072, &MPIR_Reduce_binomial_MV2},
	      {131072, -1, &MPIR_Reduce_shmem_MV2},
	    },
	  },

        }; 
        MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
		    mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table));
	return 0;
      } else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				      MV2_ARCH_AMD_OPTERON_6136_32, MV2_HCA_MLX_CX_QDR) && !heterogeneity){
        /*Trestles*/
        mv2_size_reduce_tuning_table = 6;
        mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
                                                  sizeof (mv2_reduce_tuning_table));
        mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
	  {
	    32,
	    4,
	    4,
	    {1, 0, 0, 1},
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_redscat_gather_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_binomial_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    64,
	    4,
	    4,
	    {1, 0, 1, 1},
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_binomial_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_redscat_gather_MV2},
	      {524288, -1, &MPIR_Reduce_binomial_MV2},
	    },
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    128,
	    4,
	    4,
	    {1, 0, 1, 1},
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_redscat_gather_MV2},
	      {524288, -1, &MPIR_Reduce_redscat_gather_MV2},
	    },
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_shmem_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    256,
	    4,
	    4,
	    {1, 0, 1, 1},
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_binomial_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_redscat_gather_MV2},
	      {524288, -1, &MPIR_Reduce_binomial_MV2},
	    },
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    512,
	    4,
	    4,
	    {1, 0, 1, 1},
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_binomial_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_binomial_MV2},
	    },
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
	  {
	    1024,
	    4,
	    4,
	    {1, 0, 1, 1},
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_binomial_MV2},
	    },
	    4,
	    {
	      {0, 1024, &MPIR_Reduce_shmem_MV2},
	      {1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      {131072, 524288, &MPIR_Reduce_binomial_MV2},
	      {524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	    },
	  },
        };
        MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
		    mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table)); 
	return 0;
      } else
#elif defined (CHANNEL_NEMESIS_IB)
	if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
				 MV2_ARCH_INTEL_XEON_X5650_12, MV2_HCA_MLX_CX_QDR) && !heterogeneity){
	  mv2_size_reduce_tuning_table = 6;
	  mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
						    sizeof (mv2_reduce_tuning_table));
	  mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
            {
	      12,
	      4,
	      4,
	      {1, 1, 0, 0},
	      4,
	      {
		{0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{4096, 32768, &MPIR_Reduce_binomial_MV2},
		{32768, 262144,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{4096, 32768, &MPIR_Reduce_binomial_MV2},
	      },
	      2,
	      {
		{0, 4096, &MPIR_Reduce_shmem_MV2},
		{4096, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      24,
	      4,
	      4,
	      {1, 1, 1, 0},
	      4,
	      {
		{0, -1, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{0, 262144, &MPIR_Reduce_redscat_gather_MV2},
		{262144, 1048576, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      2,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      48,
	      4,
	      4,
	      {1, 1, 1, 0},
	      4,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 131072,  &MPIR_Reduce_binomial_MV2},
		{131072, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      2,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      96,
	      4,
	      4,
	      {1, 1, 1, 0},
	      4,
	      {
		{0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{4096, 16384,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      2,
	      {
		{0, 4096, &MPIR_Reduce_shmem_MV2},
		{4096, -1,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
	      },
            },
            {
	      192,
	      4,
	      4,
	      {1, 1, 1, 0},
	      4,
	      {
		{0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      2,
	      {
		{0, 4096, &MPIR_Reduce_shmem_MV2},
		{16384, -1, &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      384,
	      4,
	      4,
	      {1, 1, 1, 1, 0},
	      5,
	      {
		{0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{4096, 8192,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 65536,&MPIR_Reduce_binomial_MV2},
		{65536, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      3,
	      {
		{0, 4096, &MPIR_Reduce_shmem_MV2},
		{4096, 8192, &MPIR_Reduce_binomial_MV2},
		{16384, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
	  }; 
	  MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
		      mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table));
	  return 0;
	} else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
					MV2_ARCH_INTEL_XEON_E5_2680_16, MV2_HCA_MLX_CX_FDR) && !heterogeneity){
	  /*Stampede*/
	  mv2_size_reduce_tuning_table = 8;
	  mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
						    sizeof (mv2_reduce_tuning_table));
	  mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
            {
	      16,
	      4,
	      4,
	      {1, 0, 0},
	      3,
	      {
		{0, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{262144, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      2,
	      {
		{0, 65536, &MPIR_Reduce_shmem_MV2},
		{65536,-1,  &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      32,
	      4,
	      4,
	      {1, 1, 1, 1, 0, 0, 0},
	      7,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 32768, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{32768, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{262144, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      6,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{16384, 32768, &MPIR_Reduce_shmem_MV2},
		{32768, 65536, &MPIR_Reduce_shmem_MV2},
		{65536, 262144, &MPIR_Reduce_shmem_MV2},
		{262144,-1,  &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      64,
	      4,
	      4,
	      {1, 1, 1, 1, 0},
	      5,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{262144, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      5,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_shmem_MV2},
		{65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{262144, -1, &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      128,
	      4,
	      4,
	      {1, 0, 1, 0, 1, 0},
	      6,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 262144, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{262144, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      5,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_shmem_MV2},
		{65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{262144, -1, &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      256,
	      4,
	      4,
	      {1, 1, 1, 0, 1, 1, 0},
	      7,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 32768, &MPIR_Reduce_binomial_MV2},
		{32768, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 262144, &MPIR_Reduce_binomial_MV2},
		{262144, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      6,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{16384, 32768, &MPIR_Reduce_shmem_MV2},
		{32768, 65536, &MPIR_Reduce_shmem_MV2},
		{65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{262144, -1, &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      512,
	      4,
	      4,
	      {1, 0, 1, 1, 1, 0},
	      6,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 262144, &MPIR_Reduce_binomial_MV2},
		{262144, 1048576, &MPIR_Reduce_binomial_MV2},
		{1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      5,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_shmem_MV2},
		{65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{262144, -1, &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      1024,
	      4,
	      4,
	      {1, 0, 1, 1, 1},
	      5,
	      {
		{0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{8192, 16384, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 262144, &MPIR_Reduce_binomial_MV2},
		{262144, -1, &MPIR_Reduce_binomial_MV2},
	      },
	      5,
	      {
		{0, 8192, &MPIR_Reduce_shmem_MV2},
		{8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{16384, 65536, &MPIR_Reduce_shmem_MV2},
		{65536, 262144, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{262144, -1, &MPIR_Reduce_binomial_MV2},
	      },
            },
            {
	      2048,
	      4,
	      4,
	      {1, 0, 1, 1, 1,1},
	      6,
	      {
		{0, 2048, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{2048, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{4096, 16384, &MPIR_Reduce_binomial_MV2},
		{16384, 65536, &MPIR_Reduce_binomial_MV2},
		{65536, 131072, &MPIR_Reduce_binomial_MV2},
		{131072, -1, &MPIR_Reduce_binomial_MV2},
	      },
	      6,
	      {
		{0, 2048, &MPIR_Reduce_shmem_MV2},
		{2048, 4096, &MPIR_Reduce_shmem_MV2},
		{4096, 16384, &MPIR_Reduce_shmem_MV2},
		{16384, 65536, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{65536, 131072, &MPIR_Reduce_binomial_MV2},
		{131072, -1, &MPIR_Reduce_shmem_MV2},
	      },
            },

	  }; 
	  MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
		      mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table));
	  return 0;
	} else if (MV2_IS_ARCH_HCA_TYPE(MV2_get_arch_hca_type(),
					MV2_ARCH_AMD_OPTERON_6136_32, MV2_HCA_MLX_CX_QDR) && !heterogeneity){
	  /*Trestles*/
	  mv2_size_reduce_tuning_table = 6;
	  mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
						    sizeof (mv2_reduce_tuning_table));
	  mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
            {
	      32,
	      4,
	      4,
	      {1, 0, 0, 1},
	      4,
	      {
		{0, 1024, &MPIR_Reduce_redscat_gather_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      4,
	      {
		{0, 1024, &MPIR_Reduce_binomial_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      64,
	      4,
	      4,
	      {1, 0, 1, 1},
	      4,
	      {
		{0, 1024, &MPIR_Reduce_binomial_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_redscat_gather_MV2},
		{524288, -1, &MPIR_Reduce_binomial_MV2},
	      },
	      4,
	      {
		{0, 1024, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      128,
	      4,
	      4,
	      {1, 0, 1, 1},
	      4,
	      {
		{0, 1024, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_redscat_gather_MV2},
		{524288, -1, &MPIR_Reduce_redscat_gather_MV2},
	      },
	      4,
	      {
		{0, 1024, &MPIR_Reduce_shmem_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      256,
	      4,
	      4,
	      {1, 0, 1, 1},
	      4,
	      {
		{0, 1024, &MPIR_Reduce_binomial_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_redscat_gather_MV2},
		{524288, -1, &MPIR_Reduce_binomial_MV2},
	      },
	      4,
	      {
		{0, 1024, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      512,
	      4,
	      4,
	      {1, 0, 1, 1},
	      4,
	      {
		{0, 1024, &MPIR_Reduce_binomial_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_binomial_MV2},
	      },
	      4,
	      {
		{0, 1024, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
            {
	      1024,
	      4,
	      4,
	      {1, 0, 1, 1},
	      4,
	      {
		{0, 1024, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_binomial_MV2},
	      },
	      4,
	      {
		{0, 1024, &MPIR_Reduce_shmem_MV2},
		{1024, 131072, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		{131072, 524288, &MPIR_Reduce_binomial_MV2},
		{524288, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
	      },
            },
	  };
	  MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
		      mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table)); 
	  return 0;
	} else
#endif
#endif /* !CHANNEL_PSM */
	  {
	    mv2_size_reduce_tuning_table = 7;
	    mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
						      sizeof (mv2_reduce_tuning_table));
	    mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[] = {
	      {
                8,
                4,
                4,
                {1, 0, 0},
                3,
                {
		  {0, 524288, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {524288, 1048576, &MPIR_Reduce_binomial_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                2,
                {
		  {0, 131072, &MPIR_Reduce_shmem_MV2},
		  {131072, -1, &MPIR_Reduce_binomial_MV2},
                },
	      },
	      {
                16,
                4,
                4,
                {1, 0},
                2,
                {
		  {0, 1048576, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                2,
                {
		  {0, 8192, &MPIR_Reduce_shmem_MV2},
		  {8192, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
                },
	      },
	      {
                32,
                4,
                4,
                {1, 1, 1, 0},
                4,
                {
		  {0, 8192, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {8192, 131072,  &MPIR_Reduce_binomial_MV2},
		  {131072, 1048576, &MPIR_Reduce_redscat_gather_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                3,
                {
		  {0, 8192, &MPIR_Reduce_shmem_MV2},
		  {8192, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
                },
	      },
	      {
                64,
                4,
                4,
                {1, 0, 1, 1, 0},
                5,
                {
		  {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {4096, 16384,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {16384, 131072,&MPIR_Reduce_binomial_MV2},
		  {131072, 1048576, &MPIR_Reduce_redscat_gather_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                4,
                {
		  {0, 4096, &MPIR_Reduce_shmem_MV2},
		  {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		  {16384, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
                },
	      },
	      {
                128,
                4,
                4,
                {1, 0, 1, 1, 0},
                5,
                {
		  {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {4096, 16384,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {16384, 131072,&MPIR_Reduce_binomial_MV2},
		  {131072, 1048576, &MPIR_Reduce_binomial_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                4,
                {
		  {0, 4096, &MPIR_Reduce_shmem_MV2},
		  {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		  {16384, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
                },
	      },
	      {
                256,
                4,
                4,
                {1, 0, 1, 1, 0},
                5,
                {
		  {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {4096, 16384,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {16384, 131072,&MPIR_Reduce_binomial_MV2},
		  {131072, 1048576, &MPIR_Reduce_binomial_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                4,
                {
		  {0, 4096, &MPIR_Reduce_shmem_MV2},
		  {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		  {16384, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
                },
	      },
	      {
                512,
                4,
                4,
                {1, 0, 1, 1, 0},
                5,
                {
		  {0, 4096, &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {4096, 16384,  &MPIR_Reduce_inter_knomial_wrapper_MV2},
		  {16384, 131072,&MPIR_Reduce_binomial_MV2},
		  {131072, 1048576, &MPIR_Reduce_binomial_MV2},
		  {1048576, -1, &MPIR_Reduce_redscat_gather_MV2},
                },
                4,
                {
		  {0, 4096, &MPIR_Reduce_shmem_MV2},
		  {8192, 16384, &MPIR_Reduce_intra_knomial_wrapper_MV2},
		  {16384, -1, &MPIR_Reduce_intra_knomial_wrapper_MV2},
                },
	      },

	    };
	    MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table,
			mv2_size_reduce_tuning_table * sizeof (mv2_reduce_tuning_table));
	    return 0;
	  }
    }
    return 0;
}

void MV2_cleanup_reduce_tuning_table()
{
  if (mv2_use_indexed_tuning || mv2_use_indexed_reduce_tuning) {
    MPIU_Free(mv2_reduce_indexed_thresholds_table[0]);
    MPIU_Free(mv2_reduce_indexed_table_ppn_conf);
    MPIU_Free(mv2_size_reduce_indexed_tuning_table);
    if (mv2_reduce_indexed_thresholds_table != NULL) {
      MPIU_Free(mv2_reduce_indexed_thresholds_table);
    }
  }
  else {
    if (mv2_reduce_thresholds_table != NULL) {
        MPIU_Free(mv2_reduce_thresholds_table);
    }
  }
}

/* Return the number of separator inside a string */
static int count_sep(char *string)
{
    return *string == '\0' ? 0 : (count_sep(string + 1) + (*string == ','));
}


int MV2_internode_Reduce_is_define(char *mv2_user_reduce_inter, char
                                    *mv2_user_reduce_intra)
{
  int i = 0;
  int nb_element = count_sep(mv2_user_reduce_inter) + 1;
  if (mv2_use_indexed_tuning || mv2_use_indexed_reduce_tuning) {

    /* If one reduce tuning table is already defined */
    if (mv2_reduce_indexed_thresholds_table != NULL) {
      if (mv2_reduce_indexed_thresholds_table[0] != NULL) {
          MPIU_Free(mv2_reduce_indexed_thresholds_table[0]);
      }
      MPIU_Free(mv2_reduce_indexed_thresholds_table);
    }

    mv2_reduce_indexed_tuning_table mv2_tmp_reduce_indexed_thresholds_table[1];
    mv2_reduce_indexed_num_ppn_conf = 1;
    if (mv2_size_reduce_indexed_tuning_table == NULL) {
        mv2_size_reduce_indexed_tuning_table =
	  MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
    }
    mv2_size_reduce_indexed_tuning_table[0] = 1;

    if (mv2_reduce_indexed_table_ppn_conf == NULL) {
        mv2_reduce_indexed_table_ppn_conf =
	  MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf * sizeof(int));
    }
    /* -1 indicates user defined algorithm */
    mv2_reduce_indexed_table_ppn_conf[0] = -1;

    /* We realloc the space for the new reduce tuning table */
    mv2_reduce_indexed_thresholds_table =
      MPIU_Malloc(mv2_reduce_indexed_num_ppn_conf *
		  sizeof(mv2_reduce_indexed_tuning_table *));
    mv2_reduce_indexed_thresholds_table[0] =
      MPIU_Malloc(mv2_size_reduce_indexed_tuning_table[0] *
		  sizeof(mv2_reduce_indexed_tuning_table));

    if (nb_element == 1) {
      mv2_tmp_reduce_indexed_thresholds_table[0].numproc = 1;
      mv2_tmp_reduce_indexed_thresholds_table[0].inter_k_degree = 4;
      mv2_tmp_reduce_indexed_thresholds_table[0].intra_k_degree = 4;
      mv2_tmp_reduce_indexed_thresholds_table[0].size_inter_table = 1;
      mv2_tmp_reduce_indexed_thresholds_table[0].size_intra_table = 1;
      mv2_tmp_reduce_indexed_thresholds_table[0].inter_leader[0].msg_sz = 1;
      mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].msg_sz = 1;

      switch (atoi(mv2_user_reduce_inter)) {
      case REDUCE_BINOMIAL:
	mv2_tmp_reduce_indexed_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_binomial_MV2;
	break;
      case REDUCE_INTER_KNOMIAL:
	mv2_tmp_reduce_indexed_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_inter_knomial_wrapper_MV2;
	break;
      case REDUCE_RDSC_GATHER:
	mv2_tmp_reduce_indexed_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_redscat_gather_MV2;
	break;
#if defined(CHANNEL_MRAIL_GEN2)
      case REDUCE_ZCPY:
	mv2_tmp_reduce_indexed_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_Zcpy_MV2;
	break;
#endif
      default:
	mv2_tmp_reduce_indexed_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_inter_knomial_wrapper_MV2;
      }
    }
    
    mv2_tmp_reduce_indexed_thresholds_table[0].size_intra_table = 2;
    if (mv2_user_reduce_intra != NULL) {
      nb_element = count_sep(mv2_user_reduce_intra) + 1;

      if (nb_element == 1) {
        mv2_tmp_reduce_indexed_thresholds_table[0].size_intra_table = 1;
        mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].msg_sz = 1;
        mv2_tmp_reduce_indexed_thresholds_table[0].intra_k_degree = 4;
        mv2_tmp_reduce_indexed_thresholds_table[0].inter_k_degree = 4;

        if(mv2_user_reduce_two_level == 1){
	  mv2_tmp_reduce_indexed_thresholds_table[0].is_two_level_reduce[0]=1;
        } else {
	  mv2_tmp_reduce_indexed_thresholds_table[0].is_two_level_reduce[0]=0;
        }
    
        switch (atoi(mv2_user_reduce_intra)) {
	case REDUCE_BINOMIAL:
	  mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
	    &MPIR_Reduce_binomial_MV2;
	  break;
	case REDUCE_INTRA_KNOMIAL:
	  mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
	    &MPIR_Reduce_intra_knomial_wrapper_MV2;
	  break;
	case REDUCE_SHMEM:
	  mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
	    &MPIR_Reduce_shmem_MV2;
	  break;
	default:
	  mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
	    &MPIR_Reduce_intra_knomial_wrapper_MV2;
        }
      }
    } else {
      mv2_tmp_reduce_indexed_thresholds_table[0].size_intra_table = 1;
      mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].msg_sz = 1;
      mv2_tmp_reduce_indexed_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
	&MPIR_Reduce_binomial_MV2;
    }
    
    MPIU_Memcpy(mv2_reduce_indexed_thresholds_table[0], mv2_tmp_reduce_indexed_thresholds_table, 
                sizeof(mv2_reduce_indexed_tuning_table));
  }
  else {

    /* If one reduce tuning table is already defined */
    if (mv2_reduce_thresholds_table != NULL) {
      MPIU_Free(mv2_reduce_thresholds_table);
    }

    mv2_reduce_tuning_table mv2_tmp_reduce_thresholds_table[1];
    mv2_size_reduce_tuning_table = 1;

    /* We realloc the space for the new reduce tuning table */
    mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
					      sizeof (mv2_reduce_tuning_table));

    if (nb_element == 1) {

      if(mv2_user_reduce_two_level == 1){
	mv2_tmp_reduce_thresholds_table[0].is_two_level_reduce[0]=1;
      } else {
	mv2_tmp_reduce_thresholds_table[0].is_two_level_reduce[0]=0;
      }

      mv2_tmp_reduce_thresholds_table[0].numproc = 1;
      mv2_tmp_reduce_thresholds_table[0].size_inter_table = 1;
      mv2_tmp_reduce_thresholds_table[0].size_intra_table = 1;
      mv2_tmp_reduce_thresholds_table[0].inter_leader[0].min = 0;
      mv2_tmp_reduce_thresholds_table[0].inter_leader[0].max = -1;
      mv2_tmp_reduce_thresholds_table[0].intra_node[0].min = 0;
      mv2_tmp_reduce_thresholds_table[0].intra_node[0].max = -1;
      mv2_tmp_reduce_thresholds_table[0].intra_k_degree = 4;
      mv2_tmp_reduce_thresholds_table[0].inter_k_degree = 4;
    
      switch (atoi(mv2_user_reduce_inter)) {
      case REDUCE_BINOMIAL:
	mv2_tmp_reduce_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_binomial_MV2;
	break;
      case REDUCE_INTER_KNOMIAL:
	mv2_tmp_reduce_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_inter_knomial_wrapper_MV2;
	break;
      case REDUCE_RDSC_GATHER:
	mv2_tmp_reduce_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_redscat_gather_MV2;
	break;
#if defined(CHANNEL_MRAIL_GEN2)
      case REDUCE_ZCPY:
	mv2_tmp_reduce_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_Zcpy_MV2;
	break;
#endif
      default:
	mv2_tmp_reduce_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	  &MPIR_Reduce_inter_knomial_wrapper_MV2;
      }
        
    } else {
      char *dup, *p, *save_p;
      regmatch_t match[NMATCH];
      regex_t preg;
      const char *regexp = "([0-9]+):([0-9]+)-([0-9]+|\\+)";

      if (!(dup = MPIU_Strdup(mv2_user_reduce_inter))) {
	fprintf(stderr, "failed to duplicate `%s'\n", mv2_user_reduce_inter);
	return 1;
      }

      if (regcomp(&preg, regexp, REG_EXTENDED)) {
	fprintf(stderr, "failed to compile regexp `%s'\n", mv2_user_reduce_inter);
	MPIU_Free(dup);
	return 2;
      }

      mv2_tmp_reduce_thresholds_table[0].numproc = 1;
      mv2_tmp_reduce_thresholds_table[0].size_inter_table = nb_element;
      mv2_tmp_reduce_thresholds_table[0].size_intra_table = 2;
      mv2_tmp_reduce_thresholds_table[0].intra_k_degree = 4;
      mv2_tmp_reduce_thresholds_table[0].inter_k_degree = 4;

      i = 0;
      for (p = strtok_r(dup, ",", &save_p); p; p = strtok_r(NULL, ",", &save_p)) {
	if (regexec(&preg, p, NMATCH, match, 0)) {
	  fprintf(stderr, "failed to match on `%s'\n", p);
	  regfree(&preg);
	  MPIU_Free(dup);
	  return 2;
	}
	/* given () start at 1 */
	switch (atoi(p + match[1].rm_so)) {
	case REDUCE_BINOMIAL:
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[i].MV2_pt_Reduce_function =
	    &MPIR_Reduce_binomial_MV2;
	  break;
	case REDUCE_INTER_KNOMIAL:
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[i].MV2_pt_Reduce_function =
	    &MPIR_Reduce_inter_knomial_wrapper_MV2;
	  break;
	case REDUCE_RDSC_GATHER:
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[i].MV2_pt_Reduce_function =
	    &MPIR_Reduce_redscat_gather_MV2;
	  break;
#if defined(CHANNEL_MRAIL_GEN2)
	case REDUCE_ZCPY:
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[0].MV2_pt_Reduce_function =
	    &MPIR_Reduce_Zcpy_MV2;
	  break;
#endif
	default:
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[i].MV2_pt_Reduce_function =
	    &MPIR_Reduce_inter_knomial_wrapper_MV2;
	}

	mv2_tmp_reduce_thresholds_table[0].inter_leader[i].min = atoi(p +
								      match[2].rm_so);
	if (p[match[3].rm_so] == '+') {
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[i].max = -1;
	} else {
	  mv2_tmp_reduce_thresholds_table[0].inter_leader[i].max =
	    atoi(p + match[3].rm_so);
	}
	i++;
      }
      MPIU_Free(dup);
      regfree(&preg);
    }
    mv2_tmp_reduce_thresholds_table[0].size_intra_table = 2;

    MPIU_Memcpy(mv2_reduce_thresholds_table, mv2_tmp_reduce_thresholds_table, sizeof
                (mv2_reduce_tuning_table));
    if (mv2_user_reduce_intra != NULL) {
      MV2_intranode_Reduce_is_define(mv2_user_reduce_intra);
    } else {
      mv2_reduce_thresholds_table[0].size_intra_table = 1;
      mv2_reduce_thresholds_table[0].intra_node[0].min = 0;
      mv2_reduce_thresholds_table[0].intra_node[0].max = -1;
      mv2_reduce_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
	&MPIR_Reduce_binomial_MV2;
    }
  }
    return 0;
}


int MV2_intranode_Reduce_is_define(char *mv2_user_reduce_intra)
{
    int i = 0;
    int nb_element = count_sep(mv2_user_reduce_intra) + 1;

    /* It is possible that tuning table is not allocated yet.
     * E.g., user only forces intra-node algorithm
     * In such case, inter-node algorithm should be selected automatically based
     * on the architecture detection in the function above */
    mv2_size_reduce_tuning_table = 1;
    if (mv2_reduce_thresholds_table == NULL)
        mv2_reduce_thresholds_table = MPIU_Malloc(mv2_size_reduce_tuning_table *
                                                    sizeof (mv2_reduce_tuning_table));

    if (nb_element == 1) {
        mv2_reduce_thresholds_table[0].size_intra_table = 1;
        mv2_reduce_thresholds_table[0].intra_node[0].min = 0;
        mv2_reduce_thresholds_table[0].intra_node[0].max = -1;
        mv2_reduce_thresholds_table[0].intra_k_degree = 4;
        mv2_reduce_thresholds_table[0].inter_k_degree = 4;

        if(mv2_user_reduce_two_level == 1){
            mv2_reduce_thresholds_table[0].is_two_level_reduce[0]=1;
        } else {
            mv2_reduce_thresholds_table[0].is_two_level_reduce[0]=0;
        }
    
        switch (atoi(mv2_user_reduce_intra)) {
            case REDUCE_BINOMIAL:
                mv2_reduce_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
                    &MPIR_Reduce_binomial_MV2;
                break;
            case REDUCE_INTRA_KNOMIAL:
                mv2_reduce_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
                    &MPIR_Reduce_intra_knomial_wrapper_MV2;
                break;
            case REDUCE_SHMEM:
                mv2_reduce_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
                    &MPIR_Reduce_shmem_MV2;
                break;
            default:
                mv2_reduce_thresholds_table[0].intra_node[0].MV2_pt_Reduce_function =
                    &MPIR_Reduce_intra_knomial_wrapper_MV2;
        }
        
    } else {
        char *dup, *p, *save_p;
        regmatch_t match[NMATCH];
        regex_t preg;
        const char *regexp = "([0-9]+):([0-9]+)-([0-9]+|\\+)";

        if (!(dup = MPIU_Strdup(mv2_user_reduce_intra))) {
            fprintf(stderr, "failed to duplicate `%s'\n", mv2_user_reduce_intra);
            return 1;
        }

        if (regcomp(&preg, regexp, REG_EXTENDED)) {
            fprintf(stderr, "failed to compile regexp `%s'\n", mv2_user_reduce_intra);
            MPIU_Free(dup);
            return 2;
        }

        mv2_reduce_thresholds_table[0].numproc = 1;
        mv2_reduce_thresholds_table[0].size_intra_table = 2;
        mv2_reduce_thresholds_table[0].intra_k_degree = 4;
        mv2_reduce_thresholds_table[0].inter_k_degree = 4;

        i = 0;
        for (p = strtok_r(dup, ",", &save_p); p; p = strtok_r(NULL, ",", &save_p)) {
            if (regexec(&preg, p, NMATCH, match, 0)) {
                fprintf(stderr, "failed to match on `%s'\n", p);
                regfree(&preg);
                MPIU_Free(dup);
                return 2;
            }
            /* given () start at 1 */
            switch (atoi(p + match[1].rm_so)) {
                case REDUCE_BINOMIAL:
                    mv2_reduce_thresholds_table[0].intra_node[i].MV2_pt_Reduce_function =
                        &MPIR_Reduce_binomial_MV2;
                    break;
                case REDUCE_INTRA_KNOMIAL:
                    mv2_reduce_thresholds_table[0].intra_node[i].MV2_pt_Reduce_function =
                        &MPIR_Reduce_intra_knomial_wrapper_MV2;
                    break;
                case REDUCE_SHMEM:
                    mv2_reduce_thresholds_table[0].intra_node[i].MV2_pt_Reduce_function =
                        &MPIR_Reduce_shmem_MV2;
                    break;
                default:
                    mv2_reduce_thresholds_table[0].intra_node[i].MV2_pt_Reduce_function =
                        &MPIR_Reduce_intra_knomial_wrapper_MV2;
            }

            mv2_reduce_thresholds_table[0].intra_node[i].min = atoi(p +
                                                                         match[2].rm_so);
            if (p[match[3].rm_so] == '+') {
                mv2_reduce_thresholds_table[0].intra_node[i].max = -1;
            } else {
                mv2_reduce_thresholds_table[0].intra_node[i].max =
                    atoi(p + match[3].rm_so);
            }
            i++;
        }
        MPIU_Free(dup);
        regfree(&preg);
    }
    return 0;
}
