/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Written (W) 1999-2008 Gunnar Raetsch
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef __GUIHMM__H
#define __GUIHMM__H

#include "lib/config.h"

#ifndef HAVE_SWIG
#include "base/SGObject.h"
#include "distributions/hmm/HMM.h"
#include "features/Labels.h"

class CSGInterface;

class CGUIHMM : public CSGObject
{
	public:
		CGUIHMM(CSGInterface* interface);
		~CGUIHMM();

		/** create new HMM */
		bool new_hmm(int32_t n, int32_t m);
		/** load HMM from file */
		bool load(char* filename);
		/** save HMM to file */
		bool save(char* filename, bool is_binary=false);

		bool set_num_hmm_tables(char* param) ;
		/** train Baum-Welch */
		bool baum_welch_train();
		/** train Baum-Welch trans */
		bool baum_welch_trans_train();
		bool baum_welch_train_defined();
		/** train Viterbi defined */
		bool viterbi_train_defined();
		/** train Viterbi */
		bool viterbi_train();
		bool linear_train(char align='l');
		bool linear_train_from_file(char* param);
		/** test HMM ONE_CLASS */
		bool one_class_test(
				char* filename_out, char* filename_roc, bool is_linear);
		/** test HMM */
		bool hmm_test(
				char* filename_out, char* filename_roc,
				bool is_pos_linear, bool is_neg_linear);
		bool hmm_classify(char* param);
		/** append HMM/model for CmdlineInterface */
		bool append_model(char* filename, int32_t base1=-1, int32_t base2=-1);
		/** add states to HMM */
		bool add_states(int32_t num_states=1, float64_t value=0);
		/** set HMM as POS/NEG/TEST */
		bool set_hmm_as(char* target);
		/** set HMM pseudo */
		bool set_pseudo(float64_t pseudo);
		/** set convergence criteria */
		bool convergence_criteria(
			int32_t num_iterations=100, float64_t epsilon=0.001);
		/** output HMM */
		bool output_hmm();
		/** output HMM defined */
		bool output_hmm_defined();
		/** print best path */
		bool best_path(int32_t from=0, int32_t to=100);
		bool normalize(bool keep_dead_states=false);
		bool save_path(char* filename, bool is_binary=false);
		/** save HMM likelihood  to file */
		bool save_likelihood(char* filename, bool is_binary=false);
		bool load_definitions(char* filename, bool do_init=false);
		bool set_max_dim(char* param);
		/** HMM likelihood */
		bool likelihood();
		/** chop HMM */
		bool chop(float64_t value);
		bool relative_entropy(float64_t*& values, int32_t& len);
		bool entropy(float64_t*& values, int32_t& len);
		/** define permutation entropy */
		bool permutation_entropy(int32_t width=0, int32_t seq_num=-1);
		inline CHMM* get_pos() { return pos; }
		inline CHMM* get_neg() { return neg; }
		inline CHMM* get_test() { return test; }
		inline void set_current(CHMM* h) { working=h; }
		inline CHMM* get_current() { return working; }
		inline float64_t get_pseudo() { return PSEUDO; }

		CLabels* classify(CLabels* output=NULL);
		float64_t classify_example(int32_t idx);
		CLabels* one_class_classify(CLabels* output=NULL);
		CLabels* linear_one_class_classify(CLabels* output=NULL);
		float64_t one_class_classify_example(int32_t idx);

	protected:
		bool converge(float64_t x, float64_t y);
		void switch_model(CHMM** m1, CHMM** m2);

		CHMM* working;

		CHMM* pos;
		CHMM* neg;
		CHMM* test;

		float64_t PSEUDO;
		int32_t M;

	protected:
		CSGInterface* ui;
};
#endif //HAVE_SWIG
#endif
