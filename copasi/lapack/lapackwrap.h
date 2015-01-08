// Copyright (C) 2013 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_lapackwrap
#define COPASI_lapackwrap

#ifdef HAVE_LAPACKWRAP_H
# include <lapackwrap.h>
#else

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

extern "C"
{
#if (defined HAVE_MKL || (defined WIN32 && defined HAVE_LAPACK_H))
# define cbdsqr_ CBDSQR
# define cgbbrd_ CGBBRD
# define cgbcon_ CGBCON
# define cgbequ_ CGBEQU
# define cgbrfs_ CGBRFS
# define cgbsv_ CGBSV
# define cgbsvx_ CGBSVX
# define cgbtf2_ CGBTF2
# define cgbtrf_ CGBTRF
# define cgbtrs_ CGBTRS
# define cgebak_ CGEBAK
# define cgebal_ CGEBAL
# define cgebd2_ CGEBD2
# define cgebrd_ CGEBRD
# define cgecon_ CGECON
# define cgeequ_ CGEEQU
# define cgees_ CGEES
# define cgeesx_ CGEESX
# define cgeev_ CGEEV
# define cgeevx_ CGEEVX
# define cgegs_ CGEGS
# define cgegv_ CGEGV
# define cgehd2_ CGEHD2
# define cgehrd_ CGEHRD
# define cgelq2_ CGELQ2
# define cgelqf_ CGELQF
# define cgels_ CGELS
# define cgelsx_ CGELSX
# define cgelsy_ CGELSY
# define cgeql2_ CGEQL2
# define cgeqlf_ CGEQLF
# define cgeqp3_ CGEQP3
# define cgeqpf_ CGEQPF
# define cgeqr2_ CGEQR2
# define cgeqrf_ CGEQRF
# define cgerfs_ CGERFS
# define cgerq2_ CGERQ2
# define cgerqf_ CGERQF
# define cgesc2_ CGESC2
# define cgesv_ CGESV
# define cgesvx_ CGESVX
# define cgetc2_ CGETC2
# define cgetf2_ CGETF2
# define cgetrf_ CGETRF
# define cgetri_ CGETRI
# define cgetrs_ CGETRS
# define cggbak_ CGGBAK
# define cggbal_ CGGBAL
# define cgges_ CGGES
# define cggesx_ CGGESX
# define cggev_ CGGEV
# define cggevx_ CGGEVX
# define cggglm_ CGGGLM
# define cgghrd_ CGGHRD
# define cgglse_ CGGLSE
# define cggqrf_ CGGQRF
# define cggrqf_ CGGRQF
# define cggsvd_ CGGSVD
# define cggsvp_ CGGSVP
# define cgtcon_ CGTCON
# define cgtrfs_ CGTRFS
# define cgtsv_ CGTSV
# define cgtsvx_ CGTSVX
# define cgttrf_ CGTTRF
# define cgttrs_ CGTTRS
# define cgtts2_ CGTTS2
# define chbev_ CHBEV
# define chbevd_ CHBEVD
# define chbevx_ CHBEVX
# define chbgst_ CHBGST
# define chbgv_ CHBGV
# define chbgvx_ CHBGVX
# define chbtrd_ CHBTRD
# define checon_ CHECON
# define cheev_ CHEEV
# define cheevd_ CHEEVD
# define cheevr_ CHEEVR
# define cheevx_ CHEEVX
# define chegs2_ CHEGS2
# define chegst_ CHEGST
# define chegv_ CHEGV
# define chegvd_ CHEGVD
# define chegvx_ CHEGVX
# define cherfs_ CHERFS
# define chesv_ CHESV
# define chesvx_ CHESVX
# define chetf2_ CHETF2
# define chetrd_ CHETRD
# define chetrf_ CHETRF
# define chetri_ CHETRI
# define chetrs_ CHETRS
# define chgeqz_ CHGEQZ
# define chpcon_ CHPCON
# define chpev_ CHPEV
# define chpevd_ CHPEVD
# define chpevx_ CHPEVX
# define chpgst_ CHPGST
# define chpgv_ CHPGV
# define chpgvd_ CHPGVD
# define chpgvx_ CHPGVX
# define chprfs_ CHPRFS
# define chpsv_ CHPSV
# define chpsvx_ CHPSVX
# define chptrd_ CHPTRD
# define chptrf_ CHPTRF
# define chptri_ CHPTRI
# define chptrs_ CHPTRS
# define chsein_ CHSEIN
# define chseqr_ CHSEQR
# define clabrd_ CLABRD
# define clacgv_ CLACGV
# define clacon_ CLACON
# define clacp2_ CLACP2
# define clacpy_ CLACPY
# define clacrm_ CLACRM
# define clacrt_ CLACRT
# define claed0_ CLAED0
# define claed7_ CLAED7
# define claed8_ CLAED8
# define claein_ CLAEIN
# define claesy_ CLAESY
# define claev2_ CLAEV2
# define clags2_ CLAGS2
# define clagtm_ CLAGTM
# define clahef_ CLAHEF
# define clahqr_ CLAHQR
# define clahrd_ CLAHRD
# define claic1_ CLAIC1
# define clals0_ CLALS0
# define clalsa_ CLALSA
# define clapll_ CLAPLL
# define clapmt_ CLAPMT
# define claqgb_ CLAQGB
# define claqge_ CLAQGE
# define claqhb_ CLAQHB
# define claqhe_ CLAQHE
# define claqhp_ CLAQHP
# define claqp2_ CLAQP2
# define claqps_ CLAQPS
# define claqsb_ CLAQSB
# define claqsp_ CLAQSP
# define claqsy_ CLAQSY
# define clar1v_ CLAR1V
# define clar2v_ CLAR2V
# define clarcm_ CLARCM
# define clarf_ CLARF
# define clarfb_ CLARFB
# define clarfg_ CLARFG
# define clarft_ CLARFT
# define clarfx_ CLARFX
# define clargv_ CLARGV
# define clarnv_ CLARNV
# define clarrv_ CLARRV
# define clartg_ CLARTG
# define clartv_ CLARTV
# define clarz_ CLARZ
# define clarzb_ CLARZB
# define clarzt_ CLARZT
# define clascl_ CLASCL
# define claset_ CLASET
# define clasr_ CLASR
# define classq_ CLASSQ
# define claswp_ CLASWP
# define clasyf_ CLASYF
# define clatbs_ CLATBS
# define clatdf_ CLATDF
# define clatps_ CLATPS
# define clatrd_ CLATRD
# define clatrs_ CLATRS
# define clatrz_ CLATRZ
# define clatzm_ CLATZM
# define clauu2_ CLAUU2
# define clauum_ CLAUUM
# define cpbcon_ CPBCON
# define cpbequ_ CPBEQU
# define cpbrfs_ CPBRFS
# define cpbstf_ CPBSTF
# define cpbsv_ CPBSV
# define cpbsvx_ CPBSVX
# define cpbtf2_ CPBTF2
# define cpbtrf_ CPBTRF
# define cpbtrs_ CPBTRS
# define cpocon_ CPOCON
# define cpoequ_ CPOEQU
# define cporfs_ CPORFS
# define cposv_ CPOSV
# define cposvx_ CPOSVX
# define cpotf2_ CPOTF2
# define cpotrf_ CPOTRF
# define cpotri_ CPOTRI
# define cpotrs_ CPOTRS
# define cppcon_ CPPCON
# define cppequ_ CPPEQU
# define cpprfs_ CPPRFS
# define cppsv_ CPPSV
# define cppsvx_ CPPSVX
# define cpptrf_ CPPTRF
# define cpptri_ CPPTRI
# define cpptrs_ CPPTRS
# define cptcon_ CPTCON
# define cptrfs_ CPTRFS
# define cptsv_ CPTSV
# define cptsvx_ CPTSVX
# define cpttrf_ CPTTRF
# define cpttrs_ CPTTRS
# define cptts2_ CPTTS2
# define crot_ CROT
# define cspcon_ CSPCON
# define cspmv_ CSPMV
# define cspr_ CSPR
# define csprfs_ CSPRFS
# define cspsv_ CSPSV
# define cspsvx_ CSPSVX
# define csptrf_ CSPTRF
# define csptri_ CSPTRI
# define csptrs_ CSPTRS
# define csrot_ CSROT
# define csrscl_ CSRSCL
# define cstedc_ CSTEDC
# define cstein_ CSTEIN
# define csteqr_ CSTEQR
# define csycon_ CSYCON
# define csymv_ CSYMV
# define csyr_ CSYR
# define csyrfs_ CSYRFS
# define csysv_ CSYSV
# define csysvx_ CSYSVX
# define csytf2_ CSYTF2
# define csytrf_ CSYTRF
# define csytri_ CSYTRI
# define csytrs_ CSYTRS
# define ctbcon_ CTBCON
# define ctbrfs_ CTBRFS
# define ctbtrs_ CTBTRS
# define ctgevc_ CTGEVC
# define ctgex2_ CTGEX2
# define ctgexc_ CTGEXC
# define ctgsen_ CTGSEN
# define ctgsja_ CTGSJA
# define ctgsna_ CTGSNA
# define ctgsy2_ CTGSY2
# define ctgsyl_ CTGSYL
# define ctpcon_ CTPCON
# define ctprfs_ CTPRFS
# define ctptri_ CTPTRI
# define ctptrs_ CTPTRS
# define ctrcon_ CTRCON
# define ctrevc_ CTREVC
# define ctrexc_ CTREXC
# define ctrrfs_ CTRRFS
# define ctrsen_ CTRSEN
# define ctrsna_ CTRSNA
# define ctrsyl_ CTRSYL
# define ctrti2_ CTRTI2
# define ctrtri_ CTRTRI
# define ctrtrs_ CTRTRS
# define ctzrqf_ CTZRQF
# define ctzrzf_ CTZRZF
# define cung2l_ CUNG2L
# define cung2r_ CUNG2R
# define cungbr_ CUNGBR
# define cunghr_ CUNGHR
# define cungl2_ CUNGL2
# define cunglq_ CUNGLQ
# define cungql_ CUNGQL
# define cungqr_ CUNGQR
# define cungr2_ CUNGR2
# define cungrq_ CUNGRQ
# define cungtr_ CUNGTR
# define cunm2l_ CUNM2L
# define cunm2r_ CUNM2R
# define cunmbr_ CUNMBR
# define cunmhr_ CUNMHR
# define cunml2_ CUNML2
# define cunmlq_ CUNMLQ
# define cunmql_ CUNMQL
# define cunmqr_ CUNMQR
# define cunmr2_ CUNMR2
# define cunmr3_ CUNMR3
# define cunmrq_ CUNMRQ
# define cunmrz_ CUNMRZ
# define cunmtr_ CUNMTR
# define cupgtr_ CUPGTR
# define cupmtr_ CUPMTR
# define dbdsdc_ DBDSDC
# define dbdsqr_ DBDSQR
# define ddisna_ DDISNA
# define dgbbrd_ DGBBRD
# define dgbcon_ DGBCON
# define dgbequ_ DGBEQU
# define dgbrfs_ DGBRFS
# define dgbsv_ DGBSV
# define dgbsvx_ DGBSVX
# define dgbtf2_ DGBTF2
# define dgbtrf_ DGBTRF
# define dgbtrs_ DGBTRS
# define dgebak_ DGEBAK
# define dgebal_ DGEBAL
# define dgebd2_ DGEBD2
# define dgebrd_ DGEBRD
# define dgecon_ DGECON
# define dgeequ_ DGEEQU
# define dgees_ DGEES
# define dgeesx_ DGEESX
# define dgeev_ DGEEV
# define dgeevx_ DGEEVX
# define dgegs_ DGEGS
# define dgegv_ DGEGV
# define dgehd2_ DGEHD2
# define dgehrd_ DGEHRD
# define dgelq2_ DGELQ2
# define dgelqf_ DGELQF
# define dgels_ DGELS
# define dgelsd_ DGELSD
# define dgelss_ DGELSS
# define dgelsx_ DGELSX
# define dgelsy_ DGELSY
# define dgeql2_ DGEQL2
# define dgeqlf_ DGEQLF
# define dgeqp3_ DGEQP3
# define dgeqpf_ DGEQPF
# define dgeqr2_ DGEQR2
# define dgeqrf_ DGEQRF
# define dgerfs_ DGERFS
# define dgerq2_ DGERQ2
# define dgerqf_ DGERQF
# define dgesc2_ DGESC2
# define dgesdd_ DGESDD
# define dgesv_ DGESV
# define dgesvd_ DGESVD
# define dgesvx_ DGESVX
# define dgetc2_ DGETC2
# define dgetf2_ DGETF2
# define dgetrf_ DGETRF
# define dgetri_ DGETRI
# define dgetrs_ DGETRS
# define dggbak_ DGGBAK
# define dggbal_ DGGBAL
# define dgges_ DGGES
# define dggesx_ DGGESX
# define dggev_ DGGEV
# define dggevx_ DGGEVX
# define dggglm_ DGGGLM
# define dgghrd_ DGGHRD
# define dgglse_ DGGLSE
# define dggqrf_ DGGQRF
# define dggrqf_ DGGRQF
# define dggsvd_ DGGSVD
# define dggsvp_ DGGSVP
# define dgtcon_ DGTCON
# define dgtrfs_ DGTRFS
# define dgtsv_ DGTSV
# define dgtsvx_ DGTSVX
# define dgttrf_ DGTTRF
# define dgttrs_ DGTTRS
# define dgtts2_ DGTTS2
# define dhgeqz_ DHGEQZ
# define dhsein_ DHSEIN
# define dhseqr_ DHSEQR
# define dlabad_ DLABAD
# define dlabrd_ DLABRD
# define dlacon_ DLACON
# define dlacpy_ DLACPY
# define dladiv_ DLADIV
# define dlae2_ DLAE2
# define dlaebz_ DLAEBZ
# define dlaed0_ DLAED0
# define dlaed1_ DLAED1
# define dlaed2_ DLAED2
# define dlaed3_ DLAED3
# define dlaed4_ DLAED4
# define dlaed5_ DLAED5
# define dlaed6_ DLAED6
# define dlaed7_ DLAED7
# define dlaed8_ DLAED8
# define dlaed9_ DLAED9
# define dlaeda_ DLAEDA
# define dlaein_ DLAEIN
# define dlaev2_ DLAEV2
# define dlaexc_ DLAEXC
# define dlag2_ DLAG2
# define dlags2_ DLAGS2
# define dlagtf_ DLAGTF
# define dlagtm_ DLAGTM
# define dlagts_ DLAGTS
# define dlagv2_ DLAGV2
# define dlahqr_ DLAHQR
# define dlahrd_ DLAHRD
# define dlaic1_ DLAIC1
# define dlaln2_ DLALN2
# define dlals0_ DLALS0
# define dlalsa_ DLALSA
# define dlalsd_ DLALSD
# define dlamc1_ DLAMC1
# define dlamc2_ DLAMC2
# define dlamc4_ DLAMC4
# define dlamc5_ DLAMC5
# define dlamrg_ DLAMRG
# define dlanv2_ DLANV2
# define dlapll_ DLAPLL
# define dlapmt_ DLAPMT
# define dlaqgb_ DLAQGB
# define dlaqge_ DLAQGE
# define dlaqp2_ DLAQP2
# define dlaqps_ DLAQPS
# define dlaqsb_ DLAQSB
# define dlaqsp_ DLAQSP
# define dlaqsy_ DLAQSY
# define dlaqtr_ DLAQTR
# define dlar1v_ DLAR1V
# define dlar2v_ DLAR2V
# define dlarf_ DLARF
# define dlarfb_ DLARFB
# define dlarfg_ DLARFG
# define dlarft_ DLARFT
# define dlarfx_ DLARFX
# define dlargv_ DLARGV
# define dlarnv_ DLARNV
# define dlarrb_ DLARRB
# define dlarre_ DLARRE
# define dlarrf_ DLARRF
# define dlarrv_ DLARRV
# define dlartg_ DLARTG
# define dlartv_ DLARTV
# define dlaruv_ DLARUV
# define dlarz_ DLARZ
# define dlarzb_ DLARZB
# define dlarzt_ DLARZT
# define dlas2_ DLAS2
# define dlascl_ DLASCL
# define dlasd0_ DLASD0
# define dlasd1_ DLASD1
# define dlasd2_ DLASD2
# define dlasd3_ DLASD3
# define dlasd4_ DLASD4
# define dlasd5_ DLASD5
# define dlasd6_ DLASD6
# define dlasd7_ DLASD7
# define dlasd8_ DLASD8
# define dlasd9_ DLASD9
# define dlasda_ DLASDA
# define dlasdq_ DLASDQ
# define dlasdt_ DLASDT
# define dlaset_ DLASET
# define dlasq1_ DLASQ1
# define dlasq2_ DLASQ2
# define dlasq3_ DLASQ3
# define dlasq4_ DLASQ4
# define dlasq5_ DLASQ5
# define dlasq6_ DLASQ6
# define dlasr_ DLASR
# define dlasrt_ DLASRT
# define dlassq_ DLASSQ
# define dlasv2_ DLASV2
# define dlaswp_ DLASWP
# define dlasy2_ DLASY2
# define dlasyf_ DLASYF
# define dlatbs_ DLATBS
# define dlatdf_ DLATDF
# define dlatps_ DLATPS
# define dlatrd_ DLATRD
# define dlatrs_ DLATRS
# define dlatrz_ DLATRZ
# define dlatzm_ DLATZM
# define dlauu2_ DLAUU2
# define dlauum_ DLAUUM
# define dopgtr_ DOPGTR
# define dopmtr_ DOPMTR
# define dorg2l_ DORG2L
# define dorg2r_ DORG2R
# define dorgbr_ DORGBR
# define dorghr_ DORGHR
# define dorgl2_ DORGL2
# define dorglq_ DORGLQ
# define dorgql_ DORGQL
# define dorgqr_ DORGQR
# define dorgr2_ DORGR2
# define dorgrq_ DORGRQ
# define dorgtr_ DORGTR
# define dorm2l_ DORM2L
# define dorm2r_ DORM2R
# define dormbr_ DORMBR
# define dormhr_ DORMHR
# define dorml2_ DORML2
# define dormlq_ DORMLQ
# define dormql_ DORMQL
# define dormqr_ DORMQR
# define dormr2_ DORMR2
# define dormr3_ DORMR3
# define dormrq_ DORMRQ
# define dormrz_ DORMRZ
# define dormtr_ DORMTR
# define dpbcon_ DPBCON
# define dpbequ_ DPBEQU
# define dpbrfs_ DPBRFS
# define dpbstf_ DPBSTF
# define dpbsv_ DPBSV
# define dpbsvx_ DPBSVX
# define dpbtf2_ DPBTF2
# define dpbtrf_ DPBTRF
# define dpbtrs_ DPBTRS
# define dpocon_ DPOCON
# define dpoequ_ DPOEQU
# define dporfs_ DPORFS
# define dposv_ DPOSV
# define dposvx_ DPOSVX
# define dpotf2_ DPOTF2
# define dpotrf_ DPOTRF
# define dpotri_ DPOTRI
# define dpotrs_ DPOTRS
# define dppcon_ DPPCON
# define dppequ_ DPPEQU
# define dpprfs_ DPPRFS
# define dppsv_ DPPSV
# define dppsvx_ DPPSVX
# define dpptrf_ DPPTRF
# define dpptri_ DPPTRI
# define dpptrs_ DPPTRS
# define dptcon_ DPTCON
# define dpteqr_ DPTEQR
# define dptrfs_ DPTRFS
# define dptsv_ DPTSV
# define dptsvx_ DPTSVX
# define dpttrf_ DPTTRF
# define dpttrs_ DPTTRS
# define dptts2_ DPTTS2
# define drscl_ DRSCL
# define dsbev_ DSBEV
# define dsbevd_ DSBEVD
# define dsbevx_ DSBEVX
# define dsbgst_ DSBGST
# define dsbgv_ DSBGV
# define dsbgvd_ DSBGVD
# define dsbgvx_ DSBGVX
# define dsbtrd_ DSBTRD
# define dspcon_ DSPCON
# define dspev_ DSPEV
# define dspevd_ DSPEVD
# define dspevx_ DSPEVX
# define dspgst_ DSPGST
# define dspgv_ DSPGV
# define dspgvd_ DSPGVD
# define dspgvx_ DSPGVX
# define dsprfs_ DSPRFS
# define dspsv_ DSPSV
# define dspsvx_ DSPSVX
# define dsptrd_ DSPTRD
# define dsptrf_ DSPTRF
# define dsptri_ DSPTRI
# define dsptrs_ DSPTRS
# define dstebz_ DSTEBZ
# define dstedc_ DSTEDC
# define dstegr_ DSTEGR
# define dstein_ DSTEIN
# define dsteqr_ DSTEQR
# define dsterf_ DSTERF
# define dstev_ DSTEV
# define dstevd_ DSTEVD
# define dstevr_ DSTEVR
# define dstevx_ DSTEVX
# define dsycon_ DSYCON
# define dsyev_ DSYEV
# define dsyevd_ DSYEVD
# define dsyevr_ DSYEVR
# define dsyevx_ DSYEVX
# define dsygs2_ DSYGS2
# define dsygst_ DSYGST
# define dsygv_ DSYGV
# define dsygvd_ DSYGVD
# define dsygvx_ DSYGVX
# define dsyrfs_ DSYRFS
# define dsysv_ DSYSV
# define dsysvx_ DSYSVX
# define dsytd2_ DSYTD2
# define dsytf2_ DSYTF2
# define dsytrd_ DSYTRD
# define dsytrf_ DSYTRF
# define dsytri_ DSYTRI
# define dsytrs_ DSYTRS
# define dtbcon_ DTBCON
# define dtbrfs_ DTBRFS
# define dtbtrs_ DTBTRS
# define dtgevc_ DTGEVC
# define dtgex2_ DTGEX2
# define dtgexc_ DTGEXC
# define dtgsen_ DTGSEN
# define dtgsja_ DTGSJA
# define dtgsna_ DTGSNA
# define dtgsy2_ DTGSY2
# define dtgsyl_ DTGSYL
# define dtpcon_ DTPCON
# define dtprfs_ DTPRFS
# define dtptri_ DTPTRI
# define dtptrs_ DTPTRS
# define dtrcon_ DTRCON
# define dtrevc_ DTREVC
# define dtrexc_ DTREXC
# define dtrrfs_ DTRRFS
# define dtrsen_ DTRSEN
# define dtrsna_ DTRSNA
# define dtrsyl_ DTRSYL
# define dtrti2_ DTRTI2
# define dtrtri_ DTRTRI
# define dtrtrs_ DTRTRS
# define dtzrqf_ DTZRQF
# define dtzrzf_ DTZRZF
# define icmax1_ ICMAX1
# define ieeeck_ IEEECK_
# define ilaenv_ ILAENV
# define izmax1_ IZMAX1
# define sbdsdc_ SBDSDC
# define sbdsqr_ SBDSQR
# define sdisna_ SDISNA
# define sgbbrd_ SGBBRD
# define sgbcon_ SGBCON
# define sgbequ_ SGBEQU
# define sgbrfs_ SGBRFS
# define sgbsv_ SGBSV
# define sgbsvx_ SGBSVX
# define sgbtf2_ SGBTF2
# define sgbtrf_ SGBTRF
# define sgbtrs_ SGBTRS
# define sgebak_ SGEBAK
# define sgebal_ SGEBAL
# define sgebd2_ SGEBD2
# define sgebrd_ SGEBRD
# define sgecon_ SGECON
# define sgeequ_ SGEEQU
# define sgees_ SGEES
# define sgeesx_ SGEESX
# define sgeev_ SGEEV
# define sgeevx_ SGEEVX
# define sgegs_ SGEGS
# define sgegv_ SGEGV
# define sgehd2_ SGEHD2
# define sgehrd_ SGEHRD
# define sgelq2_ SGELQ2
# define sgelqf_ SGELQF
# define sgels_ SGELS
# define sgelsd_ SGELSD
# define sgelss_ SGELSS
# define sgelsx_ SGELSX
# define sgelsy_ SGELSY
# define sgeql2_ SGEQL2
# define sgeqlf_ SGEQLF
# define sgeqp3_ SGEQP3
# define sgeqpf_ SGEQPF
# define sgeqr2_ SGEQR2
# define sgeqrf_ SGEQRF
# define sgerfs_ SGERFS
# define sgerq2_ SGERQ2
# define sgerqf_ SGERQF
# define sgesc2_ SGESC2
# define sgesdd_ SGESDD
# define sgesv_ SGESV
# define sgesvd_ SGESVD
# define sgesvx_ SGESVX
# define sgetc2_ SGETC2
# define sgetf2_ SGETF2
# define sgetrf_ SGETRF
# define sgetri_ SGETRI
# define sgetrs_ SGETRS
# define sggbak_ SGGBAK
# define sggbal_ SGGBAL
# define sgges_ SGGES
# define sggesx_ SGGESX
# define sggev_ SGGEV
# define sggevx_ SGGEVX
# define sggglm_ SGGGLM
# define sgghrd_ SGGHRD
# define sgglse_ SGGLSE
# define sggqrf_ SGGQRF
# define sggrqf_ SGGRQF
# define sggsvd_ SGGSVD
# define sggsvp_ SGGSVP
# define sgtcon_ SGTCON
# define sgtrfs_ SGTRFS
# define sgtsv_ SGTSV
# define sgtsvx_ SGTSVX
# define sgttrf_ SGTTRF
# define sgttrs_ SGTTRS
# define sgtts2_ SGTTS2
# define shgeqz_ SHGEQZ
# define shsein_ SHSEIN
# define shseqr_ SHSEQR
# define slabad_ SLABAD
# define slabrd_ SLABRD
# define slacon_ SLACON
# define slacpy_ SLACPY
# define sladiv_ SLADIV
# define slae2_ SLAE2
# define slaebz_ SLAEBZ
# define slaed0_ SLAED0
# define slaed1_ SLAED1
# define slaed2_ SLAED2
# define slaed3_ SLAED3
# define slaed4_ SLAED4
# define slaed5_ SLAED5
# define slaed6_ SLAED6
# define slaed7_ SLAED7
# define slaed8_ SLAED8
# define slaed9_ SLAED9
# define slaeda_ SLAEDA
# define slaein_ SLAEIN
# define slaev2_ SLAEV2
# define slaexc_ SLAEXC
# define slag2_ SLAG2
# define slags2_ SLAGS2
# define slagtf_ SLAGTF
# define slagtm_ SLAGTM
# define slagts_ SLAGTS
# define slagv2_ SLAGV2
# define slahqr_ SLAHQR
# define slahrd_ SLAHRD
# define slaic1_ SLAIC1
# define slaln2_ SLALN2
# define slals0_ SLALS0
# define slalsa_ SLALSA
# define slalsd_ SLALSD
# define slamc1_ SLAMC1
# define slamc2_ SLAMC2
# define slamc4_ SLAMC4
# define slamc5_ SLAMC5
# define slamrg_ SLAMRG
# define slanv2_ SLANV2
# define slapll_ SLAPLL
# define slapmt_ SLAPMT
# define slaqgb_ SLAQGB
# define slaqge_ SLAQGE
# define slaqp2_ SLAQP2
# define slaqps_ SLAQPS
# define slaqsb_ SLAQSB
# define slaqsp_ SLAQSP
# define slaqsy_ SLAQSY
# define slaqtr_ SLAQTR
# define slar1v_ SLAR1V
# define slar2v_ SLAR2V
# define slarf_ SLARF
# define slarfb_ SLARFB
# define slarfg_ SLARFG
# define slarft_ SLARFT
# define slarfx_ SLARFX
# define slargv_ SLARGV
# define slarnv_ SLARNV
# define slarrb_ SLARRB
# define slarre_ SLARRE
# define slarrf_ SLARRF
# define slarrv_ SLARRV
# define slartg_ SLARTG
# define slartv_ SLARTV
# define slaruv_ SLARUV
# define slarz_ SLARZ
# define slarzb_ SLARZB
# define slarzt_ SLARZT
# define slas2_ SLAS2
# define slascl_ SLASCL
# define slasd0_ SLASD0
# define slasd1_ SLASD1
# define slasd2_ SLASD2
# define slasd3_ SLASD3
# define slasd4_ SLASD4
# define slasd5_ SLASD5
# define slasd6_ SLASD6
# define slasd7_ SLASD7
# define slasd8_ SLASD8
# define slasd9_ SLASD9
# define slasda_ SLASDA
# define slasdq_ SLASDQ
# define slasdt_ SLASDT
# define slaset_ SLASET
# define slasq1_ SLASQ1
# define slasq2_ SLASQ2
# define slasq3_ SLASQ3
# define slasq4_ SLASQ4
# define slasq5_ SLASQ5
# define slasq6_ SLASQ6
# define slasr_ SLASR
# define slasrt_ SLASRT
# define slassq_ SLASSQ
# define slasv2_ SLASV2
# define slaswp_ SLASWP
# define slasy2_ SLASY2
# define slasyf_ SLASYF
# define slatbs_ SLATBS
# define slatdf_ SLATDF
# define slatps_ SLATPS
# define slatrd_ SLATRD
# define slatrs_ SLATRS
# define slatrz_ SLATRZ
# define slatzm_ SLATZM
# define slauu2_ SLAUU2
# define slauum_ SLAUUM
# define sopgtr_ SOPGTR
# define sopmtr_ SOPMTR
# define sorg2l_ SORG2L
# define sorg2r_ SORG2R
# define sorgbr_ SORGBR
# define sorghr_ SORGHR
# define sorgl2_ SORGL2
# define sorglq_ SORGLQ
# define sorgql_ SORGQL
# define sorgqr_ SORGQR
# define sorgr2_ SORGR2
# define sorgrq_ SORGRQ
# define sorgtr_ SORGTR
# define sorm2l_ SORM2L
# define sorm2r_ SORM2R
# define sormbr_ SORMBR
# define sormhr_ SORMHR
# define sorml2_ SORML2
# define sormlq_ SORMLQ
# define sormql_ SORMQL
# define sormqr_ SORMQR
# define sormr2_ SORMR2
# define sormr3_ SORMR3
# define sormrq_ SORMRQ
# define sormrz_ SORMRZ
# define sormtr_ SORMTR
# define spbcon_ SPBCON
# define spbequ_ SPBEQU
# define spbrfs_ SPBRFS
# define spbstf_ SPBSTF
# define spbsv_ SPBSV
# define spbsvx_ SPBSVX
# define spbtf2_ SPBTF2
# define spbtrf_ SPBTRF
# define spbtrs_ SPBTRS
# define spocon_ SPOCON
# define spoequ_ SPOEQU
# define sporfs_ SPORFS
# define sposv_ SPOSV
# define sposvx_ SPOSVX
# define spotf2_ SPOTF2
# define spotrf_ SPOTRF
# define spotri_ SPOTRI
# define spotrs_ SPOTRS
# define sppcon_ SPPCON
# define sppequ_ SPPEQU
# define spprfs_ SPPRFS
# define sppsv_ SPPSV
# define sppsvx_ SPPSVX
# define spptrf_ SPPTRF
# define spptri_ SPPTRI
# define spptrs_ SPPTRS
# define sptcon_ SPTCON
# define spteqr_ SPTEQR
# define sptrfs_ SPTRFS
# define sptsv_ SPTSV
# define sptsvx_ SPTSVX
# define spttrf_ SPTTRF
# define spttrs_ SPTTRS
# define sptts2_ SPTTS2
# define srscl_ SRSCL
# define ssbev_ SSBEV
# define ssbevd_ SSBEVD
# define ssbevx_ SSBEVX
# define ssbgst_ SSBGST
# define ssbgv_ SSBGV
# define ssbgvd_ SSBGVD
# define ssbgvx_ SSBGVX
# define ssbtrd_ SSBTRD
# define sspcon_ SSPCON
# define sspev_ SSPEV
# define sspevd_ SSPEVD
# define sspevx_ SSPEVX
# define sspgst_ SSPGST
# define sspgv_ SSPGV
# define sspgvd_ SSPGVD
# define sspgvx_ SSPGVX
# define ssprfs_ SSPRFS
# define sspsv_ SSPSV
# define sspsvx_ SSPSVX
# define ssptrd_ SSPTRD
# define ssptrf_ SSPTRF
# define ssptri_ SSPTRI
# define ssptrs_ SSPTRS
# define sstebz_ SSTEBZ
# define sstedc_ SSTEDC
# define sstegr_ SSTEGR
# define sstein_ SSTEIN
# define ssteqr_ SSTEQR
# define ssterf_ SSTERF
# define sstev_ SSTEV
# define sstevd_ SSTEVD
# define sstevr_ SSTEVR
# define sstevx_ SSTEVX
# define ssycon_ SSYCON
# define ssyev_ SSYEV
# define ssyevd_ SSYEVD
# define ssyevr_ SSYEVR
# define ssyevx_ SSYEVX
# define ssygs2_ SSYGS2
# define ssygst_ SSYGST
# define ssygv_ SSYGV
# define ssygvd_ SSYGVD
# define ssygvx_ SSYGVX
# define ssyrfs_ SSYRFS
# define ssysv_ SSYSV
# define ssysvx_ SSYSVX
# define ssytd2_ SSYTD2
# define ssytf2_ SSYTF2
# define ssytrd_ SSYTRD
# define ssytrf_ SSYTRF
# define ssytri_ SSYTRI
# define ssytrs_ SSYTRS
# define stbcon_ STBCON
# define stbrfs_ STBRFS
# define stbtrs_ STBTRS
# define stgevc_ STGEVC
# define stgex2_ STGEX2
# define stgexc_ STGEXC
# define stgsen_ STGSEN
# define stgsja_ STGSJA
# define stgsna_ STGSNA
# define stgsy2_ STGSY2
# define stgsyl_ STGSYL
# define stpcon_ STPCON
# define stprfs_ STPRFS
# define stptri_ STPTRI
# define stptrs_ STPTRS
# define strcon_ STRCON
# define strevc_ STREVC
# define strexc_ STREXC
# define strrfs_ STRRFS
# define strsen_ STRSEN
# define strsna_ STRSNA
# define strsyl_ STRSYL
# define strti2_ STRTI2
# define strtri_ STRTRI
# define strtrs_ STRTRS
# define stzrqf_ STZRQF
# define stzrzf_ STZRZF
# define xerbla_ XERBLA
# define zbdsqr_ ZBDSQR
# define zdrot_ ZDROT
# define zdrscl_ ZDRSCL
# define zgbbrd_ ZGBBRD
# define zgbcon_ ZGBCON
# define zgbequ_ ZGBEQU
# define zgbrfs_ ZGBRFS
# define zgbsv_ ZGBSV
# define zgbsvx_ ZGBSVX
# define zgbtf2_ ZGBTF2
# define zgbtrf_ ZGBTRF
# define zgbtrs_ ZGBTRS
# define zgebak_ ZGEBAK
# define zgebal_ ZGEBAL
# define zgebd2_ ZGEBD2
# define zgebrd_ ZGEBRD
# define zgecon_ ZGECON
# define zgeequ_ ZGEEQU
# define zgees_ ZGEES
# define zgeesx_ ZGEESX
# define zgeev_ ZGEEV
# define zgeevx_ ZGEEVX
# define zgegs_ ZGEGS
# define zgegv_ ZGEGV
# define zgehd2_ ZGEHD2
# define zgehrd_ ZGEHRD
# define zgelq2_ ZGELQ2
# define zgelqf_ ZGELQF
# define zgels_ ZGELS
# define zgelsx_ ZGELSX
# define zgelsy_ ZGELSY
# define zgeql2_ ZGEQL2
# define zgeqlf_ ZGEQLF
# define zgeqp3_ ZGEQP3
# define zgeqpf_ ZGEQPF
# define zgeqr2_ ZGEQR2
# define zgeqrf_ ZGEQRF
# define zgerfs_ ZGERFS
# define zgerq2_ ZGERQ2
# define zgerqf_ ZGERQF
# define zgesc2_ ZGESC2
# define zgesv_ ZGESV
# define zgesvx_ ZGESVX
# define zgetc2_ ZGETC2
# define zgetf2_ ZGETF2
# define zgetrf_ ZGETRF
# define zgetri_ ZGETRI
# define zgetrs_ ZGETRS
# define zggbak_ ZGGBAK
# define zggbal_ ZGGBAL
# define zgges_ ZGGES
# define zggesx_ ZGGESX
# define zggev_ ZGGEV
# define zggevx_ ZGGEVX
# define zggglm_ ZGGGLM
# define zgghrd_ ZGGHRD
# define zgglse_ ZGGLSE
# define zggqrf_ ZGGQRF
# define zggrqf_ ZGGRQF
# define zggsvd_ ZGGSVD
# define zggsvp_ ZGGSVP
# define zgtcon_ ZGTCON
# define zgtrfs_ ZGTRFS
# define zgtsv_ ZGTSV
# define zgtsvx_ ZGTSVX
# define zgttrf_ ZGTTRF
# define zgttrs_ ZGTTRS
# define zgtts2_ ZGTTS2
# define zhbev_ ZHBEV
# define zhbevd_ ZHBEVD
# define zhbevx_ ZHBEVX
# define zhbgst_ ZHBGST
# define zhbgv_ ZHBGV
# define zhbgvx_ ZHBGVX
# define zhbtrd_ ZHBTRD
# define zhecon_ ZHECON
# define zheev_ ZHEEV
# define zheevd_ ZHEEVD
# define zheevr_ ZHEEVR
# define zheevx_ ZHEEVX
# define zhegs2_ ZHEGS2
# define zhegst_ ZHEGST
# define zhegv_ ZHEGV
# define zhegvd_ ZHEGVD
# define zhegvx_ ZHEGVX
# define zherfs_ ZHERFS
# define zhesv_ ZHESV
# define zhesvx_ ZHESVX
# define zhetf2_ ZHETF2
# define zhetrd_ ZHETRD
# define zhetrf_ ZHETRF
# define zhetri_ ZHETRI
# define zhetrs_ ZHETRS
# define zhgeqz_ ZHGEQZ
# define zhpcon_ ZHPCONLAPACK_INCLUDE_DIR
# define zhpev_ ZHPEV
# define zhpevd_ ZHPEVD
# define zhpevx_ ZHPEVX
# define zhpgst_ ZHPGST
# define zhpgv_ ZHPGV
# define zhpgvd_ ZHPGVD
# define zhpgvx_ ZHPGVX
# define zhprfs_ ZHPRFS
# define zhpsv_ ZHPSV
# define zhpsvx_ ZHPSVX
# define zhptrd_ ZHPTRD
# define zhptrf_ ZHPTRF
# define zhptri_ ZHPTRI
# define zhptrs_ ZHPTRS
# define zhsein_ ZHSEIN
# define zhseqr_ ZHSEQR
# define zlabrd_ ZLABRD
# define zlacgv_ ZLACGV
# define zlacon_ ZLACON
# define zlacp2_ ZLACP2
# define zlacpy_ ZLACPY
# define zlacrm_ ZLACRM
# define zlacrt_ ZLACRT
# define zlaed0_ ZLAED0
# define zlaed7_ ZLAED7
# define zlaed8_ ZLAED8
# define zlaein_ ZLAEIN
# define zlaesy_ ZLAESY
# define zlaev2_ ZLAEV2
# define zlags2_ ZLAGS2
# define zlagtm_ ZLAGTM
# define zlahef_ ZLAHEF
# define zlahqr_ ZLAHQR
# define zlahrd_ ZLAHRD
# define zlaic1_ ZLAIC1
# define zlals0_ ZLALS0
# define zlalsa_ ZLALSA
# define zlapll_ ZLAPLL
# define zlapmt_ ZLAPMT
# define zlaqgb_ ZLAQGB
# define zlaqge_ ZLAQGE
# define zlaqhb_ ZLAQHB
# define zlaqhe_ ZLAQHE
# define zlaqhp_ ZLAQHP
# define zlaqp2_ ZLAQP2
# define zlaqps_ ZLAQPS
# define zlaqsb_ ZLAQSB
# define zlaqsp_ ZLAQSP
# define zlaqsy_ ZLAQSY
# define zlar1v_ ZLAR1V
# define zlar2v_ ZLAR2V
# define zlarcm_ ZLARCM
# define zlarf_ ZLARF
# define zlarfb_ ZLARFB
# define zlarfg_ ZLARFG
# define zlarft_ ZLARFT
# define zlarfx_ ZLARFX
# define zlargv_ ZLARGV
# define zlarnv_ ZLARNV
# define zlarrv_ ZLARRV
# define zlartg_ ZLARTG
# define zlartv_ ZLARTV
# define zlarz_ ZLARZ
# define zlarzb_ ZLARZB
# define zlarzt_ ZLARZT
# define zlascl_ ZLASCL
# define zlaset_ ZLASET
# define zlasr_ ZLASR
# define zlassq_ ZLASSQ
# define zlaswp_ ZLASWP
# define zlasyf_ ZLASYF
# define zlatbs_ ZLATBS
# define zlatdf_ ZLATDF
# define zlatps_ ZLATPS
# define zlatrd_ ZLATRD
# define zlatrs_ ZLATRS
# define zlatrz_ ZLATRZ
# define zlatzm_ ZLATZM
# define zlauu2_ ZLAUU2
# define zlauum_ ZLAUUM
# define zpbcon_ ZPBCON
# define zpbequ_ ZPBEQU
# define zpbrfs_ ZPBRFS
# define zpbstf_ ZPBSTF
# define zpbsv_ ZPBSV
# define zpbsvx_ ZPBSVX
# define zpbtf2_ ZPBTF2
# define zpbtrf_ ZPBTRF
# define zpbtrs_ ZPBTRS
# define zpocon_ ZPOCON
# define zpoequ_ ZPOEQU
# define zporfs_ ZPORFS
# define zposv_ ZPOSV
# define zposvx_ ZPOSVX
# define zpotf2_ ZPOTF2
# define zpotrf_ ZPOTRF
# define zpotri_ ZPOTRI
# define zpotrs_ ZPOTRS
# define zppcon_ ZPPCON
# define zppequ_ ZPPEQU
# define zpprfs_ ZPPRFS
# define zppsv_ ZPPSV
# define zppsvx_ ZPPSVX
# define zpptrf_ ZPPTRF
# define zpptri_ ZPPTRI
# define zpptrs_ ZPPTRS
# define zptcon_ ZPTCON
# define zptrfs_ ZPTRFS
# define zptsv_ ZPTSV
# define zptsvx_ ZPTSVX
# define zpttrf_ ZPTTRF
# define zpttrs_ ZPTTRS
# define zptts2_ ZPTTS2
# define zrot_ ZROT
# define zspcon_ ZSPCON
# define zspmv_ ZSPMV
# define zspr_ ZSPR
# define zsprfs_ ZSPRFS
# define zspsv_ ZSPSV
# define zspsvx_ ZSPSVX
# define zsptrf_ ZSPTRF
# define zsptri_ ZSPTRI
# define zsptrs_ ZSPTRS
# define zstedc_ ZSTEDC
# define zstein_ ZSTEIN
# define zsteqr_ ZSTEQR
# define zsycon_ ZSYCON
# define zsymv_ ZSYMV
# define zsyr_ ZSYR
# define zsyrfs_ ZSYRFS
# define zsysv_ ZSYSV
# define zsysvx_ ZSYSVX
# define zsytf2_ ZSYTF2
# define zsytrf_ ZSYTRF
# define zsytri_ ZSYTRI
# define zsytrs_ ZSYTRS
# define ztbcon_ ZTBCON
# define ztbrfs_ ZTBRFS
# define ztbtrs_ ZTBTRS
# define ztgevc_ ZTGEVC
# define ztgex2_ ZTGEX2
# define ztgexc_ ZTGEXC
# define ztgsen_ ZTGSEN
# define ztgsja_ ZTGSJA
# define ztgsna_ ZTGSNA
# define ztgsy2_ ZTGSY2
# define ztgsyl_ ZTGSYL
# define ztpcon_ ZTPCON
# define ztprfs_ ZTPRFS
# define ztptri_ ZTPTRI
# define ztptrs_ ZTPTRS
# define ztrcon_ ZTRCON
# define ztrevc_ ZTREVC
# define ztrexc_ ZTREXC
# define ztrrfs_ ZTRRFS
# define ztrsen_ ZTRSEN
# define ztrsna_ ZTRSNA
# define ztrsyl_ ZTRSYL
# define ztrti2_ ZTRTI2
# define ztrtri_ ZTRTRI
# define ztrtrs_ ZTRTRS
# define ztzrqf_ ZTZRQF
# define ztzrzf_ ZTZRZF
# define zung2l_ ZUNG2L
# define zung2r_ ZUNG2R
# define zungbr_ ZUNGBR
# define zunghr_ ZUNGHR
# define zungl2_ ZUNGL2
# define zunglq_ ZUNGLQ
# define zungql_ ZUNGQL
# define zungqr_ ZUNGQR
# define zungr2_ ZUNGR2
# define zungrq_ ZUNGRQ
# define zungtr_ ZUNGTR
# define zunm2l_ ZUNM2L
# define zunm2r_ ZUNM2R
# define zunmbr_ ZUNMBR
# define zunmhr_ ZUNMHR
# define zunml2_ ZUNML2
# define zunmlq_ ZUNMLQ
# define zunmql_ ZUNMQL
# define zunmqr_ ZUNMQR
# define zunmr2_ ZUNMR2
# define zunmr3_ ZUNMR3
# define zunmrq_ ZUNMRQ
# define zunmrz_ ZUNMRZ
# define zunmtr_ ZUNMTR
# define zupgtr_ ZUPGTR
# define zupmtr_ ZUPMTR
# ifdef  USE_MKL
#  include <mkl_lapack.h>
# endif // USE_MKL
#endif // USE_MKL || (WIN32 && USE_LAPACK)

# ifdef HAVE_F2C_H
#  include <f2c.h>
# else
#  include "copasi/lapack/f2c.h"
# endif

# if defined (HAVE_LAPACK_H) && !defined(HAVE_APPLE)
#  include <lapack.h>
# else
#  undef small
#  if defined (HAVE_CLAPACK_H) && !defined(HAVE_APPLE) && !defined(COPASI_OVERWRITE_USE_LAPACK)
#   include <clapack.h>
#  else
#    if !defined(HAVE_APPLE)
#     include "copasi/lapack/lapack.h"
#    endif
#  endif
# endif

#ifdef USE_SUNPERF
# include "sunperf.h"
#endif // USE_SUNPERF
}

#ifdef HAVE_APPLE
# undef abs
# undef max
# undef min
# include <Accelerate/Accelerate.h>
# include <cmath>
using std::isnan;
#endif

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

#ifdef WIN32
#if _MSC_VER < 1600
# define min _cpp_min
# define max _cpp_max
#endif // _MSC_VER
#endif // WIN32

#endif // HAVE_LAPACKWRAP_H
#endif // COPASI_lapackwrap
