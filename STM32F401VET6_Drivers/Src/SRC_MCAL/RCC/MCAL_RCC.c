/*
 * MCAL_RCC.c
 *
 *  Created on: May 13, 2022
 *      Author: Eng- Mohamed Mokhtar
 */

#include "MCAL_RCC_Interface.h"

void MCAL_RCC_Bus_Enable_Clock(U8 AxBxENR_RCC_Bus ,U8 Peripheralx)
{
	switch(AxBxENR_RCC_Bus)
	{
		case Bus_AHB1:
			SET_BIT(RCC_SPTR->REG_RCC_AHB1ENR.RegisterAccess, Peripheralx);  break ;
		case Bus_AHB2:
			SET_BIT(RCC_SPTR->REG_RCC_AHB2ENR.RegisterAccess, Peripheralx);  break ;
		case Bus_APB1:
			SET_BIT(RCC_SPTR->REG_RCC_APB1ENR.RegisterAccess, Peripheralx);  break ;
		case Bus_APB2:
			SET_BIT(RCC_SPTR->REG_RCC_APB2ENR.RegisterAccess, Peripheralx);  break ;
		default :        /************ERROR*/             				break ;
	}
}

void MCAL_RCC_Bus_Disable_Clock(U8 AxBxENR_RCC_Bus , U8 Peripheralx)
{
	switch(AxBxENR_RCC_Bus)
	{
		case Bus_AHB1:
			CLR_BIT(RCC_SPTR->REG_RCC_AHB1ENR.RegisterAccess, Peripheralx);  break ;
		case Bus_AHB2:
			CLR_BIT(RCC_SPTR->REG_RCC_AHB2ENR.RegisterAccess, Peripheralx);  break ;
		case Bus_APB1:
			CLR_BIT(RCC_SPTR->REG_RCC_APB1ENR.RegisterAccess, Peripheralx);  break ;
		case Bus_APB2:
			CLR_BIT(RCC_SPTR->REG_RCC_APB2ENR.RegisterAccess, Peripheralx);  break ;
		default :        /************ERROR*/             				break ;
	}
}

void MCAL_RCC_Enable_Security_System(void)
{
	SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_CSSON);
}

void MCAL_RCC_Disable_Security_System(void)
{
	CLR_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_CSSON);
}

void MCAL_RCC_Init_System_CLK(void)
{
	CLR_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSION);
    CLR_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEON);
    CLR_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_PLLON);
	#if CLOCK_SOURCE == HSI		/** HSI oscillator selected as system clock**********/
		/* 1- CLK SYS --> HSI */
		CLR_BIT(RCC_SPTR->REG_RCC_CFGR.RegisterAccess, CFGR_SW0);
		CLR_BIT(RCC_SPTR->REG_RCC_CFGR.RegisterAccess, CFGR_SW1);
		/* 2- EN HSI*/
		SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSION);
		/*
		while( ( ( GET_BIT( MRCC->CR , 1 ) ) == 0 ) && ( LOC_u32TimeOut < 100000 ) ){ LOC_u32TimeOut++; }
		if( LOC_u32TimeOut >= 100000 ){ TimeOut }*/
	#elif CLOCK_SOURCE == HSE	/** HSE oscillator selected as system clock**********/
		/* 1- CLK SYS --> HSE */
		SET_BIT(RCC_SPTR->REG_RCC_CFGR.RegisterAccess, CFGR_SW0);
		CLR_BIT(RCC_SPTR->REG_RCC_CFGR.RegisterAccess, CFGR_SW1);
		#if HSE_SOURCE   == CRYSTAL
			/* 2- Disable BYP [CRYSTAL selected]*/
			CLR_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEBYP);
		#elif HSE_SOURCE == RC
			/* 2- Enable BYP  [RC selected]*/
			SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEBYP);
		#else
			/* Error*/
		#endif
		/* 3- EN HSE */
		SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEON);
		/* Bit 17 -> Checking While The HSE Clock Is Stable
		while( ( ( GET_BIT( MRCC->CR , 17 ) ) == 0 ) && ( LOC_u32TimeOut < 100000 ) ){ LOC_u32TimeOut++; }
		if( LOC_u32TimeOut >= 100000 ){ TimeOut}*/
	#elif CLOCK_SOURCE == PLL	/** PLL selected as system clock*********************/
		/* 1- System Clk  PLL */
			CLR_BIT(RCC_SPTR->REG_RCC_CFGR.RegisterAccess, CFGR_SW0);
			SET_BIT(RCC_SPTR->REG_RCC_CFGR.RegisterAccess, CFGR_SW1);
		#if PLL_SOURCE == _HSI_PLL
			/* 2- PLL source From HSI */
			CLR_BIT(RCC_SPTR->REG_RCC_PLLCFGR.RegisterAccess, PLLCFGR_PLLSRC);
			/* 3- Enable HSI */
			SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSION);
			/* while ( GET_BIT(RCC_CR, CR_HSION)==0);*/
			/* 4- Enable PLL*/
			SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_PLLON);
			/* while ( GET_BIT(RCC_CR, CR_PLLON)==0);*/
		#elif PLL_SOURCE == _HSE_PLL
			/* 2- PLL source From HSE */
			SET_BIT(RCC_SPTR->REG_RCC_PLLCFGR.RegisterAccess, PLLCFGR_PLLSRC);
			/* 3-Enable HSE */
			SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEON);
			/* while ( GET_BIT(RCC_CR, CR_HSEON)==0);*/
			/* 4- Enable PLL*/
			SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_PLLON);
			/* while ( GET_BIT(RCC_CR, CR_PLLON)==0);*/
			#if HSE_SRC == 	 CRYSTAL
				/* 5- Disable BYP [CRYSTAL selected] */
				CLR_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEBYP);
			#elif HSE_SRC == RC
				/* 6- Enable BYP  [RC selected] */
				SET_BIT(RCC_SPTR->REG_RCC_CR.RegisterAccess, CR_HSEBYP);
			#else
				/*	ERROR	*/
			#endif
		#else
			/* Error*/
		#endif
	#else
		/* Error*/
	#endif
}
