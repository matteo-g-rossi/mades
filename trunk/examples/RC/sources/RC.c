// Simulation code for RC generated by the OpenModelica Compiler 1.7.0 (r9303).

#include "modelica.h"
#include "assert.h"
#include "string.h"
#include "simulation_runtime.h"

#include "RC_functions.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "InitExt.h"
#include "PrintExt.h"
#ifdef __cplusplus
}
#endif
#include "RC_functions.c"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef _OMC_MEASURE_TIME
int measure_time_flag = 1;
#else
int measure_time_flag = 0;
#endif
#define MODEL_GUID  "{8c4e810f-3df3-4a00-8276-176fa3c9f9e0}" // to check if the init file match the model!
#define NHELP 4 // number of helper vars
#define NG 2 // number of zero crossings
#define NG_SAM 0 // number of zero crossings that are samples
#define NX 1  // number of states
#define NY 10  // number of real variables
#define NA 15  // number of alias variables
#define NP 9 // number of parameters
#define NO 0 // number of outputvar on topmodel
#define NI 0 // number of inputvar on topmodel
#define NR 0 // number of residuals for initialialization function
#define NEXT 0 // number of external objects
#define NFUNC 2 // number of functions used by the simulation
#define MAXORD 5
#define NYSTR 0 // number of alg. string variables
#define NASTR 0 // number of alias string variables
#define NPSTR 0 // number of string parameters
#define NYINT 0 // number of alg. int variables
#define NAINT 0 // number of alias int variables
#define NPINT 0 // number of int parameters
#define NYBOOL 0 // number of alg. bool variables
#define NABOOL 0 // number of alias bool variables
#define NPBOOL 1 // number of bool parameters
#define NJACVARS 0 // number of jacobian variables

static DATA* localData = 0;
#define time localData->timeValue
#define $P$old$Ptime localData->oldTime
#define $P$current_step_size globalData->current_stepsize

#ifndef _OMC_QSS
#ifdef __cplusplus
extern "C" { // adrpo: this is needed for Visual C++ compilation to work!
#endif
  const char *model_name="RC";
  const char *model_fileprefix="RC";
  const char *model_dir="";
#ifdef __cplusplus
}
#endif
#endif

const struct omc_varInfo state_names[1] = {
  {1000,"COND1","",{"ReteRC.mo",6,2,6,44,0}}
};
#define $PCOND1__varInfo state_names[0]
const struct omc_varInfo derivative_names[1] = {
  {1001,"der(COND1)","",{"ReteRC.mo",6,2,6,44,0}}
};
#define $P$DER$PCOND1__varInfo derivative_names[0]
const struct omc_varInfo algvars_names[10] = {
  {1002,"der(C1.v)","Voltage drop between the two pins (= p.v - n.v)",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",178,5,178,67,1}},
  {1003,"R1.v","Voltage drop between the two pins (= p.v - n.v)",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",178,5,178,67,1}},
  {1004,"R1.LossPower","Loss power leaving component via HeatPort",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",326,5,327,50,1}},
  {1005,"C1.p.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",51,5,56,61,1}},
  {1006,"trigger_C1_v","",{"ReteRC.mo",11,2,11,29,0}},
  {1007,"C1.n.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",89,5,94,61,1}},
  {1008,"G.p.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",7,5,12,61,1}},
  {1009,"G.p.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",13,5,18,61,1}},
  {1010,"E.n.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",89,5,94,61,1}},
  {1011,"R1.R_actual","Actual resistance = R*(1 + alpha*(T_heatPort - T_ref))",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",76,3,77,63,1}}
};
#define $P$DER$PC1$Pv__varInfo algvars_names[0]
#define $PR1$Pv__varInfo algvars_names[1]
#define $PR1$PLossPower__varInfo algvars_names[2]
#define $PC1$Pp$Pi__varInfo algvars_names[3]
#define $Ptrigger_C1_v__varInfo algvars_names[4]
#define $PC1$Pn$Pv__varInfo algvars_names[5]
#define $PG$Pp$Pv__varInfo algvars_names[6]
#define $PG$Pp$Pi__varInfo algvars_names[7]
#define $PE$Pn$Pv__varInfo algvars_names[8]
#define $PR1$PR_actual__varInfo algvars_names[9]
const struct omc_varInfo param_names[9] = {
  {1012,"R1.T","Fixed device temperature if useHeatPort = false",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",321,5,322,99,1}},
  {1013,"R1.R","Resistance at temperature T_ref",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",68,3,69,40,1}},
  {1014,"R1.T_ref","Reference temperature",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",70,3,70,78,1}},
  {1015,"R1.alpha","Temperature coefficient of resistance (R_actual = R*(1 + alpha*(T_heatPort - T_ref))",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",71,3,72,93,1}},
  {1016,"C1.C","Capacitance",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",320,5,320,54,1}},
  {1017,"threshold_C1_v","",{"ReteRC.mo",7,2,7,35,0}},
  {1018,"REACT1","",{"ReteRC.mo",8,2,8,28,0}},
  {1019,"R","",{"ReteRC.mo",9,2,9,23,0}},
  {1020,"C","",{"ReteRC.mo",10,2,10,24,0}}
};
#define $PR1$PT__varInfo param_names[0]
#define $PR1$PR__varInfo param_names[1]
#define $PR1$PT_ref__varInfo param_names[2]
#define $PR1$Palpha__varInfo param_names[3]
#define $PC1$PC__varInfo param_names[4]
#define $Pthreshold_C1_v__varInfo param_names[5]
#define $PREACT1__varInfo param_names[6]
#define $PR__varInfo param_names[7]
#define $PC__varInfo param_names[8]
const struct omc_varInfo alias_names[15] = {
  {1021,"R1.i","Current flowing from pin p to pin n",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",179,5,179,55,1}},
  {1022,"R1.p.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",51,5,56,61,1}},
  {1023,"R1.T_heatPort","Temperature of HeatPort",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",328,5,328,70,1}},
  {1024,"C1.i","Current flowing from pin p to pin n",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",179,5,179,55,1}},
  {1025,"C1.n.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",95,5,100,61,1}},
  {1026,"C1.p.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",45,5,50,61,1}},
  {1027,"E.v","Voltage between pin p and n (= p.v - n.v) as input signal",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Sources.mo",13,5,18,26,1}},
  {1028,"E.i","Current flowing from pin p to pin n",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Sources.mo",19,5,19,55,1}},
  {1029,"E.n.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",95,5,100,61,1}},
  {1030,"E.p.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",45,5,50,61,1}},
  {1031,"R1.n.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",95,5,100,61,1}},
  {1032,"R1.n.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",89,5,94,61,1}},
  {1033,"E.p.i","Current flowing into the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",51,5,56,61,1}},
  {1034,"R1.p.v","Potential at the pin",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",45,5,50,61,1}},
  {1035,"C1.v","Voltage drop between the two pins (= p.v - n.v)",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",178,5,178,67,1}}
};
#define $PR1$Pi__varInfo alias_names[0]
#define $PR1$Pp$Pi__varInfo alias_names[1]
#define $PR1$PT_heatPort__varInfo alias_names[2]
#define $PC1$Pi__varInfo alias_names[3]
#define $PC1$Pn$Pi__varInfo alias_names[4]
#define $PC1$Pp$Pv__varInfo alias_names[5]
#define $PE$Pv__varInfo alias_names[6]
#define $PE$Pi__varInfo alias_names[7]
#define $PE$Pn$Pi__varInfo alias_names[8]
#define $PE$Pp$Pv__varInfo alias_names[9]
#define $PR1$Pn$Pi__varInfo alias_names[10]
#define $PR1$Pn$Pv__varInfo alias_names[11]
#define $PE$Pp$Pi__varInfo alias_names[12]
#define $PR1$Pp$Pv__varInfo alias_names[13]
#define $PC1$Pv__varInfo alias_names[14]
const struct omc_varInfo int_alg_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo int_param_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo int_alias_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo bool_alg_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo bool_param_names[1] = {
  {1036,"R1.useHeatPort","=true, if HeatPort is enabled",{"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",319,5,320,80,1}}
};
#define $PR1$PuseHeatPort__varInfo bool_param_names[0]
const struct omc_varInfo bool_alias_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo string_alg_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo string_param_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo string_alias_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_varInfo jacobian_names[1] = {{-1,"","",omc_dummyFileInfo}};
const struct omc_functionInfo function_names[2] = {
  {1037,"Init",{"ReteRC.mo",44,1,47,9,0}},
  {1038,"FilePrint",{"ReteRC.mo",49,1,55,14,0}}
};

#define $PCOND1 localData->states[0]
#define $P$old$PCOND1 localData->states_old[0]
#define $P$old2$PCOND1 localData->states_old2[0]
#define $P$PRE$PCOND1 localData->states_saved[0]
#define $P$DER$PCOND1 localData->statesDerivatives[0]
#define $P$old$P$DER$PCOND1 localData->statesDerivatives_old[0]
#define $P$old2$P$DER$PCOND1 localData->statesDerivatives_old2[0]
#define $P$PRE$P$DER$PCOND1 localData->statesDerivatives_saved[0]
#define $P$DER$PC1$Pv localData->algebraics[0]
#define $P$old$P$DER$PC1$Pv localData->algebraics_old[0]
#define $P$old2$P$DER$PC1$Pv localData->algebraics_old2[0]
#define $P$PRE$P$DER$PC1$Pv localData->algebraics_saved[0]
#define $PR1$Pv localData->algebraics[1]
#define $P$old$PR1$Pv localData->algebraics_old[1]
#define $P$old2$PR1$Pv localData->algebraics_old2[1]
#define $P$PRE$PR1$Pv localData->algebraics_saved[1]
#define $PR1$PLossPower localData->algebraics[2]
#define $P$old$PR1$PLossPower localData->algebraics_old[2]
#define $P$old2$PR1$PLossPower localData->algebraics_old2[2]
#define $P$PRE$PR1$PLossPower localData->algebraics_saved[2]
#define $PC1$Pp$Pi localData->algebraics[3]
#define $P$old$PC1$Pp$Pi localData->algebraics_old[3]
#define $P$old2$PC1$Pp$Pi localData->algebraics_old2[3]
#define $P$PRE$PC1$Pp$Pi localData->algebraics_saved[3]
#define $Ptrigger_C1_v localData->algebraics[4]
#define $P$old$Ptrigger_C1_v localData->algebraics_old[4]
#define $P$old2$Ptrigger_C1_v localData->algebraics_old2[4]
#define $P$PRE$Ptrigger_C1_v localData->algebraics_saved[4]
#define $PC1$Pn$Pv localData->algebraics[5]
#define $P$old$PC1$Pn$Pv localData->algebraics_old[5]
#define $P$old2$PC1$Pn$Pv localData->algebraics_old2[5]
#define $P$PRE$PC1$Pn$Pv localData->algebraics_saved[5]
#define $PG$Pp$Pv localData->algebraics[6]
#define $P$old$PG$Pp$Pv localData->algebraics_old[6]
#define $P$old2$PG$Pp$Pv localData->algebraics_old2[6]
#define $P$PRE$PG$Pp$Pv localData->algebraics_saved[6]
#define $PG$Pp$Pi localData->algebraics[7]
#define $P$old$PG$Pp$Pi localData->algebraics_old[7]
#define $P$old2$PG$Pp$Pi localData->algebraics_old2[7]
#define $P$PRE$PG$Pp$Pi localData->algebraics_saved[7]
#define $PE$Pn$Pv localData->algebraics[8]
#define $P$old$PE$Pn$Pv localData->algebraics_old[8]
#define $P$old2$PE$Pn$Pv localData->algebraics_old2[8]
#define $P$PRE$PE$Pn$Pv localData->algebraics_saved[8]
#define $PR1$PR_actual localData->algebraics[9]
#define $P$old$PR1$PR_actual localData->algebraics_old[9]
#define $P$old2$PR1$PR_actual localData->algebraics_old2[9]
#define $P$PRE$PR1$PR_actual localData->algebraics_saved[9]
#define $PR1$PT localData->parameters[0]
#define $P$old$PR1$PT localData->parameters_old[0]
#define $P$old2$PR1$PT localData->parameters_old2[0]
#define $P$PRE$PR1$PT localData->parameters_saved[0]
#define $PR1$PR localData->parameters[1]
#define $P$old$PR1$PR localData->parameters_old[1]
#define $P$old2$PR1$PR localData->parameters_old2[1]
#define $P$PRE$PR1$PR localData->parameters_saved[1]
#define $PR1$PT_ref localData->parameters[2]
#define $P$old$PR1$PT_ref localData->parameters_old[2]
#define $P$old2$PR1$PT_ref localData->parameters_old2[2]
#define $P$PRE$PR1$PT_ref localData->parameters_saved[2]
#define $PR1$Palpha localData->parameters[3]
#define $P$old$PR1$Palpha localData->parameters_old[3]
#define $P$old2$PR1$Palpha localData->parameters_old2[3]
#define $P$PRE$PR1$Palpha localData->parameters_saved[3]
#define $PC1$PC localData->parameters[4]
#define $P$old$PC1$PC localData->parameters_old[4]
#define $P$old2$PC1$PC localData->parameters_old2[4]
#define $P$PRE$PC1$PC localData->parameters_saved[4]
#define $Pthreshold_C1_v localData->parameters[5]
#define $P$old$Pthreshold_C1_v localData->parameters_old[5]
#define $P$old2$Pthreshold_C1_v localData->parameters_old2[5]
#define $P$PRE$Pthreshold_C1_v localData->parameters_saved[5]
#define $PREACT1 localData->parameters[6]
#define $P$old$PREACT1 localData->parameters_old[6]
#define $P$old2$PREACT1 localData->parameters_old2[6]
#define $P$PRE$PREACT1 localData->parameters_saved[6]
#define $PR localData->parameters[7]
#define $P$old$PR localData->parameters_old[7]
#define $P$old2$PR localData->parameters_old2[7]
#define $P$PRE$PR localData->parameters_saved[7]
#define $PC localData->parameters[8]
#define $P$old$PC localData->parameters_old[8]
#define $P$old2$PC localData->parameters_old2[8]
#define $P$PRE$PC localData->parameters_saved[8]
#define $PR1$PuseHeatPort localData->boolVariables.parameters[0]
#define $P$old$PR1$PuseHeatPort localData->boolVariables.parameters_old[0]
#define $P$old2$PR1$PuseHeatPort localData->boolVariables.parameters_old2[0]
#define $P$PRE$PR1$PuseHeatPort localData->boolVariables.parameters_saved[0]
#define Init_index 0
#define FilePrint_index 1

void init_Alias(DATA* data)
{
  DATA_REAL_ALIAS omc__realAlias[15] = {
    {&$PC1$Pp$Pi,0,0},
    {&$PC1$Pp$Pi,0,1},
    {&$PR1$PT,0,2},
    {&$PC1$Pp$Pi,0,3},
    {&$PC1$Pp$Pi,1,4},
    {&$PCOND1,0,5},
    {&$PREACT1,0,6},
    {&$PC1$Pp$Pi,1,7},
    {&$PC1$Pp$Pi,0,8},
    {&$PREACT1,0,9},
    {&$PC1$Pp$Pi,1,10},
    {&$PCOND1,0,11},
    {&$PC1$Pp$Pi,1,12},
    {&$PREACT1,0,13},
    {&$PCOND1,0,14}
  };
  DATA_INT_ALIAS omc__intAlias[1] = {{0,0,-1}};
  DATA_BOOL_ALIAS omc__boolAlias[1] = {{0,0,-1}};
  DATA_STRING_ALIAS omc__stringAlias[1] = {{0,0,-1}};
if (data->nAlias)
  memcpy(data->realAlias,omc__realAlias,sizeof(DATA_REAL_ALIAS)*data->nAlias);
if (data->intVariables.nAlias)
  memcpy(data->intVariables.alias,omc__intAlias,sizeof(DATA_INT_ALIAS)*data->intVariables.nAlias);
if (data->boolVariables.nAlias)
  memcpy(data->boolVariables.alias,omc__boolAlias,sizeof(DATA_BOOL_ALIAS)*data->boolVariables.nAlias);
if (data->stringVariables.nAlias)
  memcpy(data->stringVariables.alias,omc__stringAlias,sizeof(DATA_STRING_ALIAS)*data->stringVariables.nAlias);
};

static char init_fixed[NX+NX+NY+NYINT+NYBOOL+NP+NPINT+NPBOOL] = {
  0 /* COND1 */,
  0 /* der(COND1) */,
  0 /* der(C1.v) */,
  0 /* R1.v */,
  0 /* R1.LossPower */,
  0 /* C1.p.i */,
  0 /* trigger_C1_v */,
  0 /* C1.n.v */,
  0 /* G.p.v */,
  0 /* G.p.i */,
  0 /* E.n.v */,
  0 /* R1.R_actual */,
  1 /* R1.T */,
  1 /* R1.R */,
  1 /* R1.T_ref */,
  1 /* R1.alpha */,
  1 /* C1.C */,
  1 /* threshold_C1_v */,
  1 /* REACT1 */,
  1 /* R */,
  1 /* C */,
  1 /* R1.useHeatPort */
};

char var_attr[NX+NY+NYINT+NYBOOL+NYSTR+NP+NPINT+NPBOOL+NPSTR] = {
  1+0 /* COND1 */,
  1+0 /* der(C1.v) */,
  1+0 /* R1.v */,
  1+0 /* R1.LossPower */,
  1+0 /* C1.p.i */,
  1+16 /* trigger_C1_v */,
  1+0 /* C1.n.v */,
  1+0 /* G.p.v */,
  1+0 /* G.p.i */,
  1+0 /* E.n.v */,
  1+0 /* R1.R_actual */,
  1+0 /* R1.T */,
  1+0 /* R1.R */,
  1+0 /* R1.T_ref */,
  1+0 /* R1.alpha */,
  1+0 /* C1.C */,
  1+0 /* threshold_C1_v */,
  1+0 /* REACT1 */,
  1+0 /* R */,
  1+0 /* C */,
  8+16 /* R1.useHeatPort */
};

const struct omc_varInfo *equationInfo_cref1 = &$PR1$Pv__varInfo;
const struct omc_varInfo *equationInfo_cref3 = &$PC1$Pp$Pi__varInfo;
const struct omc_varInfo *equationInfo_cref5 = &$PR1$PLossPower__varInfo;
const struct omc_varInfo *equationInfo_cref7 = &$P$DER$PC1$Pv__varInfo;
const struct omc_varInfo *equationInfo_cref9 = &$P$DER$PCOND1__varInfo;
const int nEquation = 11;
const struct omc_equationInfo equation_info[11] = {
  {1039,"SES_ALGORITHM 0",0,NULL},
  {1040,"SES_SIMPLE_ASSIGN 1",1,&equationInfo_cref1},
  {1041,"SES_ALGORITHM 2",0,NULL},
  {1042,"SES_SIMPLE_ASSIGN 3",1,&equationInfo_cref3},
  {1043,"SES_ALGORITHM 4",0,NULL},
  {1044,"SES_SIMPLE_ASSIGN 5",1,&equationInfo_cref5},
  {1045,"SES_ALGORITHM 6",0,NULL},
  {1046,"SES_SIMPLE_ASSIGN 7",1,&equationInfo_cref7},
  {1047,"SES_ALGORITHM 8",0,NULL},
  {1048,"SES_SIMPLE_ASSIGN 9",1,&equationInfo_cref9},
  {1049,"SES_ALGORITHM 10",0,NULL}
};
const int n_omc_equationInfo_reverse_prof_index = 0;
const int omc_equationInfo_reverse_prof_index[] = {
  
};

void setLocalData(DATA* data)
{
  localData = data;
  init_Alias(data);
}

DATA* initializeDataStruc()
{
  DATA* returnData = (DATA*)malloc(sizeof(DATA));

  if(!returnData) //error check
    return 0;

  memset(returnData,0,sizeof(DATA));
  returnData->nStates = NX;
  returnData->nAlgebraic = NY;
  returnData->nAlias = NA;
  returnData->nParameters = NP;
  returnData->nInputVars = NI;
  returnData->nOutputVars = NO;
  returnData->nFunctions = NFUNC;
  returnData->nEquations = nEquation;
  returnData->nProfileBlocks = n_omc_equationInfo_reverse_prof_index;
  returnData->nZeroCrossing = NG;
  returnData->nRawSamples = NG_SAM;
  returnData->nInitialResiduals = NR;
  returnData->nHelpVars = NHELP;
  returnData->stringVariables.nParameters = NPSTR;
  returnData->stringVariables.nAlgebraic = NYSTR;
  returnData->stringVariables.nAlias = NASTR;
  returnData->intVariables.nParameters = NPINT;
  returnData->intVariables.nAlgebraic = NYINT;
  returnData->intVariables.nAlias = NAINT;
  returnData->boolVariables.nParameters = NPBOOL;
  returnData->boolVariables.nAlgebraic = NYBOOL;
  returnData->boolVariables.nAlias = NABOOL;
  returnData->nJacobianvars = NJACVARS;

  returnData->initFixed = init_fixed;
  returnData->var_attr = var_attr;
  returnData->modelName = model_name;
  returnData->modelFilePrefix = model_fileprefix;
  returnData->modelGUID = MODEL_GUID;
  returnData->statesNames = state_names;
  returnData->stateDerivativesNames = derivative_names;
  returnData->algebraicsNames = algvars_names;
  returnData->int_alg_names = int_alg_names;
  returnData->bool_alg_names = bool_alg_names;
  returnData->string_alg_names = string_alg_names;
  returnData->parametersNames = param_names;
  returnData->int_param_names = int_param_names;
  returnData->bool_param_names = bool_param_names;
  returnData->string_param_names = string_param_names;
  returnData->alias_names = alias_names;
  returnData->int_alias_names = int_alias_names;
  returnData->bool_alias_names = bool_alias_names;
  returnData->string_alias_names = string_alias_names;
  returnData->jacobian_names = jacobian_names;
  returnData->functionNames = function_names;
  returnData->equationInfo = equation_info;
  returnData->equationInfo_reverse_prof_index = omc_equationInfo_reverse_prof_index;

  if (NEXT) {
    returnData->extObjs = (void**)malloc(sizeof(void*)*NEXT);
    if (!returnData->extObjs) {
      printf("error allocating external objects\n");
      exit(-2);
    }
    memset(returnData->extObjs,0,sizeof(void*)*NEXT);
  } else {
    returnData->extObjs = 0;
  }

  return returnData;
}


/* Has to be performed after _init.xml file has been read */
void callExternalObjectConstructors(DATA* localData) {
  state mem_state;
  mem_state = get_memory_state();
}


void deInitializeDataStruc(DATA* data)
{
  if (data->extObjs) {
    free(data->extObjs);
    data->extObjs = 0;
  }
}


int input_function()
{
  return 0;
}

int output_function()
{
  return 0;
}

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void function_sampleInit()
{
}

int function_updateSample()
{
  state mem_state;
  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}

int numDelayExpressionIndex = 0;
int function_storeDelayed()
{
  state mem_state;
  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}

int initial_function()
{


  
  return 0;
}

int initial_residual()
{
  int i = 0;
  state mem_state;
  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}

int bound_parameters()
{
  state mem_state;
  
  mem_state = get_memory_state();
  $PR1$PT = $PR1$PT_ref; 
  $PR1$PR = $PR; 
  $PR1$PR_actual = ($PR1$PR * (1.0 + ($PR1$Palpha * ($PR1$PT - $PR1$PT_ref)))); 
  $PC1$PC = $PC; 
  /*#modelicaLine [/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo:321:5-322:99]*/
  if (!($PR1$PT >= 0.0)) {
    omc_fileInfo info = {"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Interfaces.mo",321,5,322,99,1};
    MODELICA_ASSERT(info, "Variable R1.T out of limit");
  }
  /*#endModelicaLine*/
  /*#modelicaLine [/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo:70:3-70:78]*/
  if (!($PR1$PT_ref >= 0.0)) {
    omc_fileInfo info = {"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",70,3,70,78,1};
    MODELICA_ASSERT(info, "Variable R1.T_ref out of limit");
  }
  /*#endModelicaLine*/
  /*#modelicaLine [/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo:320:5-320:54]*/
  if (!($PC1$PC >= 0.0)) {
    omc_fileInfo info = {"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",320,5,320,54,1};
    MODELICA_ASSERT(info, "Variable C1.C out of limit");
  }
  /*#endModelicaLine*/
  restore_memory_state(mem_state);
  
  return 0;
}

int functionODE()
{
  state mem_state;
  
  mem_state = get_memory_state();
  $PR1$Pv = ($PREACT1 - $PCOND1); 
  $PC1$Pp$Pi = DIVISION($PR1$Pv,$PR1$PR_actual,"R1.v / R1.R_actual because R1.R_actual == 0"); 
  $P$DER$PC1$Pv = DIVISION($PC1$Pp$Pi,$PC1$PC,"C1.p.i / C1.C because C1.C == 0"); 
  $P$DER$PCOND1 = $P$DER$PC1$Pv; 
  restore_memory_state(mem_state);
  
  return 0;
}
#include <simulation_inline_solver.h>
const char *_omc_force_solver=_OMC_FORCE_SOLVER;
const int inline_work_states_ndims=_OMC_SOLVER_WORK_STATES_NDIMS;
int functionODE_inline()
{
  return 0;
}

int functionODE_residual(double *t, double *x, double *xd, double *delta,
                    fortran_integer *ires, double *rpar, fortran_integer *ipar)
{
  double timeBackup;
  double* statesBackup;
  int i;

  timeBackup = localData->timeValue;
  statesBackup = localData->states;

  localData->timeValue = *t;
  localData->states = x;
  functionODE();

  /* get the difference between the temp_xd(=localData->statesDerivatives)
     and xd(=statesDerivativesBackup) */
  for (i=0; i < localData->nStates; i++) {
    delta[i] = localData->statesDerivatives[i] - xd[i];
  }

  localData->states = statesBackup;
  localData->timeValue = timeBackup;

  return 0;
}

/* for continuous time variables */
int functionAlgebraics()
{
  state mem_state;
  
  mem_state = get_memory_state();
  $PR1$PLossPower = ($PR1$Pv * $PC1$Pp$Pi); 
  restore_memory_state(mem_state);
  
  return 0;
}

/* for continuous time variables */
int functionAliasEquations()
{
  state mem_state;
  modelica_boolean tmp1050;
  
  mem_state = get_memory_state();
  /*#modelicaLine [/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo:79:3-79:108]*/
  RELATIONTOZC(tmp1050, (1.0 + ($PR1$Palpha * ($PR1$PT - $PR1$PT_ref))), 1e-15, -1,GreaterEq,>=);
  if (!tmp1050) {
    omc_fileInfo info = {"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",79,3,79,108,1};
    MODELICA_ASSERT(info, "Temperature outside scope of model!");
  }
  /*#endModelicaLine*/
  restore_memory_state(mem_state);
  
  return 0;
}

int functionDAE(int *needToIterate)
{
  state mem_state;
  initial_rettype tmp1051;
  modelica_boolean tmp1052;
  modelica_boolean tmp1053;
  *needToIterate = 0;
  inUpdate=initial()?0:1;
  
  mem_state = get_memory_state();
  $PR1$Pv = ($PREACT1 - $PCOND1); 
  $PC1$Pp$Pi = DIVISION($PR1$Pv,$PR1$PR_actual,"R1.v / R1.R_actual because R1.R_actual == 0"); 
  $PR1$PLossPower = ($PR1$Pv * $PC1$Pp$Pi); 
  $P$DER$PC1$Pv = DIVISION($PC1$Pp$Pi,$PC1$PC,"C1.p.i / C1.C because C1.C == 0"); 
  $P$DER$PCOND1 = $P$DER$PC1$Pv; 
  /*#modelicaLine [ReteRC.mo:27:2-29:10]*/
  tmp1051 = initial();
  localData->helpVars[3] = tmp1051;
  if (localData->helpVars[3] && !localData->helpVars_saved[3] /* edge */) {
    /*#modelicaLine [ReteRC.mo:28:3-28:9]*/
    #ifdef _OMC_MEASURE_TIME
    SIM_PROF_TICK_FN(Init_index);
    #endif
    _Init();
    #ifdef _OMC_MEASURE_TIME
    SIM_PROF_ACC_FN(Init_index);
    #endif
    /* NORETCALL */;
    /*#endModelicaLine*/
  }
  /*#endModelicaLine*/
  /*#modelicaLine [ReteRC.mo:31:2-35:10]*/
  SAVEZEROCROSS(tmp1053, $PCOND1, $Pthreshold_C1_v, 1,Greater,>);
  localData->helpVars[1] = tmp1053;
  SAVEZEROCROSS(tmp1052, $PCOND1, $Pthreshold_C1_v, -1,LessEq,<=);
  localData->helpVars[2] = tmp1052;
  if (localData->helpVars[1] && !localData->helpVars_saved[1] /* edge */) {
    /*#modelicaLine [ReteRC.mo:32:3-32:22]*/
    $Ptrigger_C1_v = 1.0;
    /*#endModelicaLine*/
  }
  else if (localData->helpVars[2] && !localData->helpVars_saved[2] /* edge */) {
    /*#modelicaLine [ReteRC.mo:34:3-34:22]*/
    $Ptrigger_C1_v = 0.0;
    /*#endModelicaLine*/
  }
  /*#endModelicaLine*/
  /*#modelicaLine [ReteRC.mo:37:4-39:12]*/
  localData->helpVars[0] = ($Ptrigger_C1_v != $P$PRE$Ptrigger_C1_v);
  if (localData->helpVars[0] && !localData->helpVars_saved[0] /* edge */) {
    /*#modelicaLine [ReteRC.mo:38:7-38:55]*/
    #ifdef _OMC_MEASURE_TIME
    SIM_PROF_TICK_FN(FilePrint_index);
    #endif
    _FilePrint($Ptrigger_C1_v, $P$PRE$Ptrigger_C1_v, time);
    #ifdef _OMC_MEASURE_TIME
    SIM_PROF_ACC_FN(FilePrint_index);
    #endif
    /* NORETCALL */;
    /*#endModelicaLine*/
  }
  /*#endModelicaLine*/
  restore_memory_state(mem_state);
  
  inUpdate=0;
  
  return 0;
}

int function_onlyZeroCrossings(double *gout,double *t)
{
  state mem_state;
  
  mem_state = get_memory_state();
  ZEROCROSSING(0, LessEq($PCOND1, $Pthreshold_C1_v));
  ZEROCROSSING(1, Greater($PCOND1, $Pthreshold_C1_v));
  restore_memory_state(mem_state);
  
  return 0;
}

int checkForDiscreteChanges()
{
  int needToIterate = 0;

  if ($Ptrigger_C1_v != $P$PRE$Ptrigger_C1_v) { if (sim_verbose >= LOG_EVENTS) { printf("Discrete Var trigger_C1_v : %g to %g\n", $P$PRE$Ptrigger_C1_v, $Ptrigger_C1_v); }  needToIterate=1; }
  
  return needToIterate;
}

/* for continuous time variables */
int checkForAsserts()
{
  modelica_boolean tmp1054;

  /*#modelicaLine [/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo:79:3-79:108]*/
  SAVEZEROCROSS(tmp1054, (1.0 + ($PR1$Palpha * ($PR1$PT - $PR1$PT_ref))), 1e-15, -1,GreaterEq,>=);
  if (!tmp1054) {
    omc_fileInfo info = {"/usr/lib/omlibrary/Modelica 3.1/Electrical/Analog/Basic.mo",79,3,79,108,1};
    MODELICA_ASSERT(info, "Temperature outside scope of model!");
  }
  /*#endModelicaLine*/
  
  return 0;
}

int functionJacA( double *jac)
{
  state mem_state;


  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}


int functionJacB( double *jac)
{
  state mem_state;


  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}


int functionJacC( double *jac)
{
  state mem_state;


  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}


int functionJacD( double *jac)
{
  state mem_state;


  
  mem_state = get_memory_state();
  restore_memory_state(mem_state);
  
  return 0;
}


const char *linear_model_frame =
  "model linear_RC\n  parameter Integer n = 1; // states \n  parameter Integer k = 0; // top-level inputs \n  parameter Integer l = 0; // top-level outputs \n"
  "  parameter Real x0[1] = {%s};\n"
  "  parameter Real u0[0] = {%s};\n"
  "  parameter Real A[1,1] = [%s];\n"
  "  parameter Real B[1,0] = zeros(1,0);%s\n"
  "  parameter Real C[0,1] = zeros(0,1);%s\n"
  "  parameter Real D[0,0] = zeros(0,0);%s\n"
  "  Real x[1](start=x0);\n"
  "  input Real u[0];\n"
  "  output Real y[0];\n"
  "\n  Real x_PCOND1 = x[1];\n      \n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_RC;\n"
;

#ifdef __cplusplus
}
#endif

