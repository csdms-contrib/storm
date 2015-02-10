      PROGRAM STORM
C-----------------------------------------------------------------------
C This subroutine computes the windfield for a cyclone based on pressure
C distribution and radius to maximum winds (SI units).
C Variables:
C       LMAX = maximum number of timesteps over which winds computed
C	MCENT=x-dir. position of storm center at beginning.
C	NCENT=y-dir. position of storm center at beginning.
C       SVEL=storm velocity  (m/sec)
C	SDIR=storm direction (degrees counterclockwise from east)
C	PCENT=pressure at eye (Pascals)
C	PEDGE=pressure at edge (Pascals)
C	RMAXW=radius of maximum storm winds(m)
C       SRAD=storm radius (m)
C-----------------------------------------------------------------------
 
      IMPLICIT NONE
      INTEGER LMAX,I,J,IM,JM,LI,LJ,LT
      INTEGER L
      INTEGER MCENT,NCENT
      INTEGER I3,I4
      INTEGER LSC
 
      PARAMETER (LI=25,LJ=25,LT=10)
 
      REAL*8 W,TAUX(LI,LJ,LT),TAUY(LI,LJ,LT)
      REAL*8 WINDX(LI,LJ,LT),WINDY(LI,LJ,LT),WDIR(LI,LJ,LT)
      DOUBLE PRECISION DX,DY,PI,RHOA,F
      DOUBLE PRECISION SVEL,SDIR,PCENT,PEDGE,RMAXW,SRAD
      DOUBLE PRECISION WSPD,A,R,CC,PHI
      DOUBLE PRECISION USM,USMX,USMY,WSPDX,WSPDY,CD,STRESS
      DOUBLE PRECISION DX2,DY2,DEFCON,DEFX,DXT,DYT
      DOUBLE PRECISION ACOR
 
      DATA PI,RHOA/3.14159265,1.22/
      DATA F/.000061618/
      DATA ACOR/0.0/
 
      OPEN(10, FILE= './wind.in')
      OPEN(16, FILE= './WINDX.DATA')
      OPEN(17, FILE= './WINDY.DATA')
      OPEN(18, FILE= './WDIR.DATA')
 
C-----------------------------------------------------------------------
C     Read in maximum number of timesteps
C-----------------------------------------------------------------------
 
      READ (10, *) LMAX, IM, JM, DX, DY
 
      DX2 = DX*.5
      DY2 = DY*.5
      DO 3 I = 1, IM
         DO 2 J = 1, JM
            DO 1 L = 1, LMAX
               WINDX(J,I,L) = 0.0
               WINDY(J,I,L) = 0.0
    1       CONTINUE
    2    CONTINUE
    3 CONTINUE
C-----------------------------------------------------------------------
C     Start main computation koop
C-----------------------------------------------------------------------
 
      DO 6 L = 1, LMAX
 
C-----------------------------------------------------------------------
C   Read the i,j location of the storm center and other variables
C   for selected timesteps. LSC is the next timestep for which data
C   are to be read.
C   The variable SDIR must be given in degrees measured counterclockwise
C       from east.
C-----------------------------------------------------------------------
 
         IF (L .EQ. 1) THEN
            READ (10, *) MCENT, NCENT, LSC
            READ (10, *) SVEL, SDIR, PCENT, PEDGE, RMAXW, SRAD, DEFCON
            SDIR = SDIR + ACOR
            SDIR = PI*SDIR/180.
         ELSE IF (L .EQ. LSC) THEN
            READ (10, *) MCENT, NCENT, LSC
            READ (10, *) SVEL, SDIR, PCENT, PEDGE, RMAXW, SRAD, DEFCON
            SDIR = SDIR + ACOR
            SDIR = PI*SDIR/180.
         ENDIF
 
C-----------------------------------------------------------------------
C Solve the quadratic equation for windspeed at each i,j.
C Only northern hemisphere cases are considered.
C-----------------------------------------------------------------------
         DO I = 1, IM
            DO J = 1, JM
               IF (I.EQ.MCENT .AND. J.EQ.NCENT) THEN
                  WSPD = SVEL
                  PHI = SDIR
               ELSE
                  DXT = ABS((I-MCENT)*DX)
                  DYT = ABS((J-NCENT)*DY)
 
                  R = SQRT(DXT**2+DYT**2)
                  A = 1/R
                  CC = -((PEDGE-PCENT)/RHOA)*(RMAXW*(A*A))*EXP((-RMAXW*A
     #               ))
                  WSPD = ((-F)+SQRT(F*F-4.*A*CC))/(2.0*A)
 
C-----------------------------------------------------------------------
C Each node is analyzed for the angle of the wind at that position. The
C value of phi found here will be used in finding the shear stress at
C the surface.
C First, consider nodes north of the storm center.
C-----------------------------------------------------------------------
 
                  IF (J .GT. NCENT) THEN
                     IF (I .EQ. MCENT) PHI = PI
                     IF (I .LT. MCENT) PHI = ATAN(DXT/DYT) + PI
                     IF (I .GT. MCENT) PHI = ATAN(DYT/DXT) + PI/2.0
 
C-----------------------------------------------------------------------
C Second, for nodes at the same lattitude as the storm center.
C-----------------------------------------------------------------------
 
                  ELSE IF (J .EQ. NCENT) THEN
                     IF (I .LT. MCENT) PHI = 1.5*PI
                     IF (I .GT. MCENT) PHI = PI/2.0
 
C-----------------------------------------------------------------------
C Third, for nodes south of the storm center.
C-----------------------------------------------------------------------
 
                  ELSE IF (J .LT. NCENT) THEN
                     IF (I .EQ. MCENT) PHI = 0.0
                     IF (I .LT. MCENT) PHI = ATAN(DYT/DXT) + 1.5*PI
                     IF (I .GT. MCENT) PHI = ATAN(DXT/DYT)
                  ENDIF
                  PHI = PHI + DEFCON*DEFX*R/RMAXW*PI/180.
               ENDIF
 
C-----------------------------------------------------------------------
C For a moving storm a correction factor allows for increased winds.
C-----------------------------------------------------------------------
 
               USM = (RMAXW*R/(RMAXW*RMAXW+R*R))*SVEL
               USMY = USM*COS(SDIR)
               USMX = USM*SIN(SDIR)
               WSPDX = WSPD*COS(PHI) + USMX
               WSPDY = WSPD*SIN(PHI) + USMY
               WSPD = SQRT(WSPDX*WSPDX+WSPDY*WSPDY)
               WINDX(I,J,L) = WSPDX
               WINDY(I,J,L) = WSPDY
               WDIR(I,J,L) = PHI*180./PI - ACOR
C-----------------------------------------------------------------------
C Calculate the wind shear stress after first calculating the
C coefficient of drag
C-----------------------------------------------------------------------
 
               W = WSPD*.01
               IF (W .LE. 6.0) THEN
                  CD = .0011
               ELSE IF (W.GT.6.0 .AND. W.LE.22.0) THEN
                  CD = (.61+.063*W)*.001
               ELSE IF (W .GT. 22.0) THEN
                  CD = (1.0+.07*W)*.001
               ENDIF
               STRESS = CD*RHOA*WSPD*WSPD
               TAUX(I,J,L) = STRESS*COS(PHI)
               TAUY(I,J,L) = STRESS*SIN(PHI)
            END DO
         END DO
    6 CONTINUE
 
      DO L = 1, LMAX
         I3 = 1
         I4 = 7
    7    CONTINUE
         IF (I3 .LE. IM) THEN
            I4 = MIN0(IM,I4)
            WRITE (16, 100) L
            WRITE (17, 100) L
  100 FORMAT(I6)
            DO 8 J = 1, JM
               WRITE (16, 101) (WINDX(I,J,L), I = I3, I4)
               WRITE (17, 101) (WINDY(I,J,L), I = I3, I4)
               WRITE (18, 101) (WDIR(I,J,L), I = I3, I4)
  101 FORMAT(7(1X,1PE9.2))
    8       CONTINUE
            I3 = I4 + 1
            I4 = I4 + 7
            GO TO 7
         ENDIF
      END DO
      STOP 
      END
