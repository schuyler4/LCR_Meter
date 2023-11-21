<Qucs Schematic 0.0.19>
<Properties>
  <View=0,60,800,781,1,0,0>
  <Grid=10,10,1>
  <DataSet=peak_voltages.dat>
  <DataDisplay=peak_voltages.dpl>
  <OpenDisplay=1>
  <Script=peak_voltages.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <Vac V1 1 240 300 18 -26 0 1 "5V" 1 "100 Hz" 0 "0" 0 "0" 0>
  <GND * 1 400 390 0 0 0 0>
  <.TR TR1 1 230 400 0 65 0 0 "lin" 1 "0" 1 "100ms" 1 "10000" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <R R1 1 400 320 15 -26 0 1 "1000" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <C C1 1 320 240 -26 -55 0 2 "1uF" 1 "" 0 "neutral" 0>
</Components>
<Wires>
  <240 330 240 370 "" 0 0 0 "">
  <240 370 400 370 "" 0 0 0 "">
  <400 370 400 390 "" 0 0 0 "">
  <240 240 290 240 "" 0 0 0 "">
  <240 240 240 270 "" 0 0 0 "">
  <350 240 400 240 "" 0 0 0 "">
  <400 240 400 290 "" 0 0 0 "">
  <400 350 400 370 "" 0 0 0 "">
  <400 240 400 240 "output" 430 210 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
