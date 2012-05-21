/*   Copyright 2010 Juan Rada-Vilela

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */
/* 
 * File:   FuzzyLite.h
 * Author: jcrada
 *
 * Created on December 5, 2009, 9:54 PM
 */

#ifndef FL_FUZZYLITE_H
#define	FL_FUZZYLITE_H

#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/AreaCentroidAlgorithm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/CompoundTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/DescriptiveAntecedent.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/DiscreteTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FunctionTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyAnd.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyAntecedent.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyConsequent.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyDefuzzifier.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyEngine.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyException.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyExceptions.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyModulation.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperation.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperator.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOr.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyRule.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/Hedge.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/HedgeSet.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/InfixToPostfix.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/InputLVar.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/LinguisticTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/LinguisticVariable.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/MamdaniConsequent.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/MamdaniRule.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/OutputLVar.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/RectangularTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/RuleBlock.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/ShoulderTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/SingletonTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/StrOp.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TakagiSugenoConsequent.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TakagiSugenoRule.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TakagiSugenoTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TrapezoidalTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TriangularTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/defs.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/flScalar.h"

#endif	/* FL_FUZZYLITE_H */

