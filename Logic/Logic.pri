# Custom algorithm
SOURCES += \
    ../Logic/Algorithm/Custom/normal-algorithm.cpp \
    ../Logic/Algorithm/Custom/base-algorithm.cpp \
    ../Logic/Algorithm/Custom/algorithm-manager.cpp \
    ../Logic/Algorithm/Custom/one-subcycle-algorithm.cpp \
    ../Logic/Algorithm/Custom/all-subcycle-algorithm.cpp \
    ../Logic/Algorithm/Custom/helper.cpp \
    ../Logic/Algorithm/Custom/all-fuzzy-logic.cpp \
    ../Logic/Algorithm/Custom/one-fuzzy-logic.cpp

HEADERS += \
    ../Logic/Algorithm/Custom/normal-algorithm.h \
    ../Logic/Algorithm/Custom/base-algorithm.h \
    ../Logic/Algorithm/Custom/algorithm-manager.h \
    ../Logic/Algorithm/Custom/one-subcycle-algorithm.h \
    ../Logic/Algorithm/Custom/all-subcycle-algorithm.h \
    ../Logic/Algorithm/Custom/helper.h \
    ../Logic/Algorithm/Custom/all-fuzzy-logic.h \
    ../Logic/Algorithm/Custom/one-fuzzy-logic.h

# GALib
SOURCES += \
           ../Logic/Algorithm/GA/GAParameter.C \
           ../Logic/Algorithm/GA/GAStringGenome.C \
           ../Logic/Algorithm/GA/GARealGenome.C \
           ../Logic/Algorithm/GA/GAAllele.C \
           ../Logic/Algorithm/GA/GAPopulation.C \
           ../Logic/Algorithm/GA/GATreeBASE.C \
           ../Logic/Algorithm/GA/GATreeGenome.C \
           ../Logic/Algorithm/GA/GABaseGA.C \
           ../Logic/Algorithm/GA/GASelector.C \
           ../Logic/Algorithm/GA/GASimpleGA.C \
           ../Logic/Algorithm/GA/GA3DBinStrGenome.C \
           ../Logic/Algorithm/GA/GADCrowdingGA.C \
           ../Logic/Algorithm/GA/gaerror.C \
           ../Logic/Algorithm/GA/GAScaling.C \
           ../Logic/Algorithm/GA/GABin2DecGenome.C \
           ../Logic/Algorithm/GA/GA2DArrayGenome.C \
           ../Logic/Algorithm/GA/GAIncGA.C \
           ../Logic/Algorithm/GA/GA3DArrayGenome.C \
           ../Logic/Algorithm/GA/GA1DArrayGenome.C \
           ../Logic/Algorithm/GA/garandom.C \
           ../Logic/Algorithm/GA/GAStatistics.C \
           ../Logic/Algorithm/GA/GAList.C \
           ../Logic/Algorithm/GA/GADemeGA.C \
           ../Logic/Algorithm/GA/GATree.C \
           ../Logic/Algorithm/GA/GABinStr.C \
           ../Logic/Algorithm/GA/GAListBASE.C \
           ../Logic/Algorithm/GA/GAGenome.C \
           ../Logic/Algorithm/GA/gabincvt.C \
           ../Logic/Algorithm/GA/GAListGenome.C \
           ../Logic/Algorithm/GA/GA1DBinStrGenome.C \
           ../Logic/Algorithm/GA/GA2DBinStrGenome.C \
           ../Logic/Algorithm/GA/GASStateGA.C

HEADERS += \
           ../Logic/Algorithm/GA/gaid.h \
           ../Logic/Algorithm/GA/gaversion.h \
           ../Logic/Algorithm/GA/GAListBASE.h \
           ../Logic/Algorithm/GA/gatypes.h \
           ../Logic/Algorithm/GA/GA2DBinStrGenome.h \
           ../Logic/Algorithm/GA/GAGenome.h \
           ../Logic/Algorithm/GA/GA3DBinStrGenome.h \
           ../Logic/Algorithm/GA/GAScaling.h \
           ../Logic/Algorithm/GA/GABin2DecGenome.h \
           ../Logic/Algorithm/GA/GARealGenome.h \
           ../Logic/Algorithm/GA/GATreeGenome.h \
           ../Logic/Algorithm/GA/GAListGenome.h \
           ../Logic/Algorithm/GA/GADemeGA.h \
           ../Logic/Algorithm/GA/std_stream.h \
           ../Logic/Algorithm/GA/GAStatistics.h \
           ../Logic/Algorithm/GA/GANode.h \
           ../Logic/Algorithm/GA/GAList.h \
           ../Logic/Algorithm/GA/GASelector.h \
           ../Logic/Algorithm/GA/GASimpleGA.h \
           ../Logic/Algorithm/GA/GABinStr.h \
           ../Logic/Algorithm/GA/gabincvt.h \
           ../Logic/Algorithm/GA/GA1DArrayGenome.h \
           ../Logic/Algorithm/GA/garandom.h \
           ../Logic/Algorithm/GA/GASStateGA.h \
           ../Logic/Algorithm/GA/GATree.h \
           ../Logic/Algorithm/GA/GADCrowdingGA.h \
           ../Logic/Algorithm/GA/GAIncGA.h \
           ../Logic/Algorithm/GA/GABaseGA.h \
           ../Logic/Algorithm/GA/GAMask.h \
           ../Logic/Algorithm/GA/GATreeBASE.h \
           ../Logic/Algorithm/GA/gaconfig.h \
           ../Logic/Algorithm/GA/GAArray.h \
           ../Logic/Algorithm/GA/GAPopulation.h \
           ../Logic/Algorithm/GA/gaerror.h \
           ../Logic/Algorithm/GA/GAParameter.h \
           ../Logic/Algorithm/GA/ga.h \
           ../Logic/Algorithm/GA/GAStringGenome.h \
           ../Logic/Algorithm/GA/GAAllele.h \
           ../Logic/Algorithm/GA/GA2DArrayGenome.h \
           ../Logic/Algorithm/GA/GA3DArrayGenome.h \
           ../Logic/Algorithm/GA/GAEvalData.h \
           ../Logic/Algorithm/GA/GA1DBinStrGenome.h \

# FIS
SOURCES += \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/TriangularTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/TrapezoidalTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/test.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/TakagiSugenoTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/TakagiSugenoRule.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/TakagiSugenoConsequent.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/StrOp.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/SingletonTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/ShoulderTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/RuleBlock.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/RectangularTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/OutputLVar.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/MamdaniRule.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/MamdaniConsequent.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/LinguisticVariable.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/LinguisticTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/InputLVar.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/InfixToPostfix.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/HedgeSet.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/Hedge.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyRule.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyOr.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyOperator.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyOperation.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyModulation.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyExceptions.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyException.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyEngine.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyDefuzzifier.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyConsequent.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyAntecedent.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FuzzyAnd.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/FunctionTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/DiscreteTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/DescriptiveAntecedent.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/CompoundTerm.cpp \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/src/AreaCentroidAlgorithm.cpp

HEADERS += \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TriangularTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TrapezoidalTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/test.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TakagiSugenoTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TakagiSugenoRule.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TakagiSugenoConsequent.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/StrOp.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/SingletonTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/ShoulderTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/RuleBlock.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/RectangularTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/OutputLVar.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/MamdaniRule.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/MamdaniConsequent.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/main.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/LinguisticVariable.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/LinguisticTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/InputLVar.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/InfixToPostfix.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/HedgeSet.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/Hedge.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyRule.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOr.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperator.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperation.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyModulation.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyExceptions.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyException.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyEngine.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyDefuzzifier.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyConsequent.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyAntecedent.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyAnd.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FunctionTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/DiscreteTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/DescriptiveAntecedent.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/CompoundTerm.h \
    ../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/AreaCentroidAlgorithm.h



