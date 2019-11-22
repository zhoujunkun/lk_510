#ifndef __EMS_PORT_HH__
#define __EMS_PORT_HH__

void EMS_Port_Init(void);



///  no extern  Of electrodes
void Ems_A_To_Ems_B_PNAlter_P(u32 pulse);  ////   A_u->B_d   B_u->A_d  
void Ems_A_To_Ems_B_PNAlter_N(u32 pulse);  ///  B_u->A_d	A_u->B_d
void Ems_A_To_Ems_B_Single_P(u32 pulse);  //// A_u->B_d  
void Ems_A_To_Ems_B_Single_N(u32 pulse); ///  B_u->A_d
void Ems_A_To_Ems_B_Double(u32 pulse);  ///  四管同开

////  When extended to large electrode plates

void Ems_C_To_Ems_D_PNAlter_P(u32 pulse); ///  C_u->D_d   C_d->D_u
void Ems_C_To_Ems_D_PNAlter_N(u32 pulse); ///  C_d->D_u   C_u->D-d
void Ems_C_To_Ems_D_Single_P(u32 pulse); ///  C_u->D_d
void Ems_C_To_Ems_D_Single_N(u32 pulse); ///  C_d->D_u
void Ems_C_To_Ems_D_Double(u32 pulse);  //  四管同开



//The electrode was extended to 4 pieces
/*
  A-B  C-D第一组
  
*/

void Ems_A_To_Ems_B_PNAlter_Four_P(u32 pulse); /// A_u->B_d   A_D->B_u
void Ems_A_To_Ems_B_PNAlter_Four_N(u32 pulse); /// A_d->B_u   A_u->B_d
void Ems_C_To_Ems_D_PNAlter_Four_P(u32 pulse); /// C_u->D_d   C_D->D_u
void Ems_C_To_Ems_D_PNAlter_Four_N(u32 pulse); /// C_d->D_u   C_u->D_d

/*

    B-C  D-A  第二组
 
*/

void Ems_B_To_Ems_C_PNAlter_Four_P(u32 pulse); /// B_u->C_d   B_d->C_u
void Ems_B_To_Ems_C_PNAlter_Four_N(u32 pulse); /// B_d->C_u   B_u->C_d
void Ems_D_To_Ems_A_PNAlter_Four_P(u32 pulse); /// D_u->A_d   D_d->A_u
void Ems_D_To_Ems_A_PNAlter_Four_N(u32 pulse); /// D_d->A_u   D_u->A_d
/*

    A-C    B-D   斜对角  
    
*/

void Ems_A_To_Ems_C_PNAlter_Four_P(u32 pulse); /// A_u->C_d   A_d->C_u
void Ems_A_To_Ems_C_PNAlter_Four_N(u32 pulse); /// A_d->C_u   A_u->C_d
void Ems_B_To_Ems_D_PNAlter_Four_P(u32 pulse); /// B_u->D_d   B_d->D_u
void Ems_B_To_Ems_D_PNAlter_Four_N(u32 pulse); /// B_d->D_u   B_u->D_d


void Ems_A_To_Ems_B_FS_P(u32 pulse); ///  A_u->B_d
void Ems_A_To_Ems_B_FS_N(u32 pulse); ///  A_d->B_u
void Ems_C_To_Ems_D_FS_P(u32 pulse); /// C_u->D_d
void Ems_C_To_Ems_D_FS_N(u32 pulse); /// C_u->D_d
void Ems_A_To_Ems_C_FS_P(u32 pulse); ///A_u->C_d
void Ems_A_To_Ems_C_FS_N(u32 pulse);  /// A_d->C_u
void Ems_B_To_Ems_D_FS_P(u32 pulse);  /// B_u->D_d
void Ems_B_To_Ems_D_FS_N(u32 pulse); /// B_d->D_u
void Ems_B_To_Ems_C_FS_P(u32 pulse);  /// B_u->C_d
void Ems_B_To_Ems_C_FS_N(u32 pulse);  ///  B_d->C_u
void Ems_A_To_Ems_D_FS_P(u32 pulse);   //A_u->D_d
void Ems_A_To_Ems_D_FS_N(u32 pulse);  /// A_d->D_u
void Ems_AB_And_CD_Four(u32 pulse);
void Ems_AToB_Ems_CToD_FS_P(u32 pulse); /// A_u->B_d    C_u->D_d
void Ems_AToB_Ems_CToD_FS_N(u32 pulse); /// A_d->B_U    C_d->D_u

/*

   第一组  A ->B  -->B->A     C->D-->D->C   
                     

*/

void Ems_AToB_And_Ems_CToD_PNAlter_P(u32 pulse); /// A_u->B_d   C_u->D_d   <-> A_d->B_u  C_d->D_u
void Ems_AToB_And_Ems_CToD_PNAlter_N(u32 pulse); /// A_d->B_u   C_d->D_u   <-> A_u->B_d  C_u->D_d

/*

    第二组 A->C --->C->A   B->D--->D->B
 
*/

void Ems_AToC_And_Ems_BToD_PNAlter_P(u32 pulse); /// A_u->C_d   B_u->D_d   <-> A_d->C_u  B_d->D_u
void Ems_AToC_And_Ems_BToD_PNAlter_N(u32 pulse); /// A_d->C_u   B_d->D_u   <-> A_u->C_d  B_u->D_d

/*
        第三组 A->D--->D->A   B->C--->C->B
*/
void Ems_AToD_And_Ems_BToC_PNAlter_P(u32 pulse); /// A_u->D_d   B_u->C_d	 <-> A_d->D_u  B_d->C_u
void Ems_AToD_And_Ems_BToC_PNAlter_N(u32 pulse); /// A_d->D_u   B_d->C_u   <-> A_u->D_d  B_u->C_d


void Ems_AB_And_CD_Discharge(u32 pulse);
void Ems_AB_And_CD_Idle(u32 pulse);


void EmsA_T_B_And_C_T_D(u32 pulse);
void EmsA_T_B_And_D_T_C(u32 pulse);
void EmsA_T_B_And_CDAuto_PN(u32 pulse,u8* L_R);
void EmsA_T_C_And_B_T_D(u32 pulse);
void EmsA_T_C_And_D_T_B(u32 pulse);
void EmsA_T_C_And_BDAuto_PN(u32 pulse,u8* L_R);
void EmsA_T_D_And_B_T_C(u32 pulse);
void EmsA_T_D_And_C_T_B(u32 pulse);
void EmsA_T_D_And_BCAuto_PN(u32 pulse,u8* L_R);
void EmsB_T_A_And_C_T_D(u32 pulse);
void EmsB_T_A_And_D_T_C(u32 pulse);
void EmsB_T_A_And_CDAuto_PN(u32 pulse,u8* L_R);
void EmsB_T_C_And_A_T_D(u32 pulse);
void EmsB_T_C_And_D_T_A(u32 pulse);
void EmsB_T_C_And_ADAuto_PN(u32 pulse,u8* L_R);
void EmsB_T_D_And_A_T_C(u32 pulse);
void EmsB_T_D_And_C_T_A(u32 pulse);
void EmsB_T_D_And_ACAuto_PN(u32 pulse,u8* L_R);
void EmsC_T_A_And_B_T_D(u32 pulse);
void EmsC_T_A_And_D_T_B(u32 pulse);
void EmsC_T_A_And_BDAuto_PN(u32 pulse,u8* L_R);
void EmsC_T_B_And_A_T_D(u32 pulse);
void EmsC_T_B_And_D_T_A(u32 pulse);
void EmsC_T_B_And_ADAuto_PN(u32 pulse,u8* L_R);
void EmsC_T_D_And_A_T_B(u32 pulse);
void EmsC_T_D_And_B_T_A(u32 pulse);
void EmsC_T_D_And_ABAuto_PN(u32 pulse,u8* L_R);
void EmsD_T_A_And_C_T_B(u32 pulse);
void EmsD_T_A_And_B_T_C(u32 pulse);
void EmsD_T_A_And_BC_AutO_PN(u32 pulse,u8* L_R);
void Ems_A_T_B_And_CD_No_PN(u32 pulse,u8* L_R);
void EmsA_T_C_And_BD_No_PN(u32 pulse,u8* L_R);
void EmsA_T_D_And_BC_No_PN(u32 pulse,u8* L_R);
void EmsB_T_A_And_CD_No_PN(u32 pulse,u8* L_R);
void EmsB_T_C_And_AD_No_PN(u32 pulse,u8* L_R);
void EmsB_T_D_And_AC_No_PN(u32 pulse,u8* L_R);
void EmsC_T_A_And_BD_No_PN(u32 pulse,u8* L_R);
void EmsC_T_B_And_AD_No_PN(u32 pulse,u8* L_R);
void EmsC_T_D_And_AB_No_PN(u32 pulse,u8* L_R);
void EmsD_T_A_And_BC_No_PN(u32 pulse,u8*L_R);
void EmsD_T_B_And_AC_No_PN(u32 pulse,u8*L_R);
void EmsD_T_C_And_AB_No_PN(u32 pulse,u8* L_R);
void EmsABC_T_D_PN(u32 pulse,u8*L_R);
void EmsABD_T_C_PN(u32 pulse,u8*L_R);
void EmsACD_T_B_PN(u32 pulse,u8*L_R);
void EmsBCD_T_A_PN(u32 pulse,u8*L_R);

void EmsC_T_A_And_BD_No(u32 pulse);
void EmsC_T_B_And_AD_No(u32 pulse);
void EmsC_T_D_And_AB_No(u32 pulse);
void EmsABAuto_And_CDAuto_PN(u32 pulse,u8*L_R);
void EmsACAutO_And_BDAuto_PN(u32 pulse,u8*L_R);
void EmsADAuto_And_BCAuto_PN(u32 pulse,u8*L_R);

#endif
