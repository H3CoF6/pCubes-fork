        if not VarExists('R') then
          R := 1;


        // Vertices (corners)

        dAngle := (Arctan(2) + Arcsin(2/3)) / 2;
        dAngle2 := (Arctan(2) - Arcsin(2/3)) / 2;
        //phi := (Sqrt(5) - 1) / 2; // The golden ratio
        //dAngle := Arctan(phi) + Arctan(1 - phi); // := Arctan((3 + sqrt(5)) / 4);
        //dAngle2 := Arctan(phi) - Arctan(1 - phi); // := Arctan((3 - sqrt(5)) / 4);

        Rsin := R * sin(dAngle); // R * sqrt((5 + 2 * sqrt(5)) / 15);
        Rcos := R * cos(dAngle); // R * sqrt((10 - 2 * sqrt(5)) / 15);
        R2sin := R * sin(dAngle2); // R * sqrt((5 - 2 * sqrt(5)) / 15);
        R2cos := R * cos(dAngle2); // R * sqrt((10 + 2 * sqrt(5)) / 15);
        sAngle := Pi * 2 / 5;

        for i := 0 to 4 do begin
            Vx[i] := Rcos * sin(sAngle * (i - 0.5));
            Vy[i] := Rcos * cos(sAngle * (i - 0.5));
            Vz[i] := Rsin;
        end;

        for i := 5 to 9 do begin
            Vx[i] := R2cos * sin(sAngle * (i - 0.5));
            Vy[i] := R2cos * cos(sAngle * (i - 0.5));
            Vz[i] := R2sin;
        end;

        for i := 10 to 14 do begin
            Vx[i] := R2cos * sin(sAngle * i);
            Vy[i] := R2cos * cos(sAngle * i);
            Vz[i] := -R2sin;
        end;

        for i := 15 to 19 do begin
            Vx[i] := Rcos * sin(sAngle * i);
            Vy[i] := Rcos * cos(sAngle * i);
            Vz[i] := -Rsin;
        end;


        // Centers

        mAngle := ArcTan(0.5);
        As := sin(mAngle); // 1/sqrt(5)
        Ac := cos(mAngle); // 2/sqrt(5)
        sAngle := PI * 2 / 5;
        Cx[0] := 0;
        Cy[0] := 0;
        Cz[0] := RSin;

        for i := 1 to 5 do begin
            Cx[i] := RSin * sin(sAngle * (i - 1)) * Ac;
            Cy[i] := RSin * cos(sAngle * (i - 1)) * Ac;
            Cz[i] := RSin * As;
        end;

        for i := 6 to 10 do begin
            Cx[i] := -Cx[i - 5];
            Cy[i] := -Cy[i - 5];
            Cz[i] := -Cz[i - 5];
        end;
        Cx[11] := 0;
        Cy[11] := 0;
        Cz[11] := -RSin;


        // Edges
//        procedure CalcEdgeCenter(i, i1, i2); -- // shows error duplicating procedure name, i.e. Big Chop
//        begin
//            Ex[i] := (Vx[i1] + Vx[i2]) / 2;
//            Ey[i] := (Vy[i1] + Vy[i2]) / 2;
//            Ez[i] := (Vz[i1] + Vz[i2]) / 2;
//        end;
//        CalcEdgeCenter( 0,  0,  1);
//        . . .


        Ex[ 0] := (Vx[ 0] + Vx[ 1]) / 2; Ey[ 0] := (Vy[ 0] + Vy[ 1]) / 2; Ez[ 0] := (Vz[ 0] + Vz[ 1]) / 2;
        Ex[ 1] := (Vx[ 1] + Vx[ 2]) / 2; Ey[ 1] := (Vy[ 1] + Vy[ 2]) / 2; Ez[ 1] := (Vz[ 1] + Vz[ 2]) / 2;
        Ex[ 2] := (Vx[ 2] + Vx[ 3]) / 2; Ey[ 2] := (Vy[ 2] + Vy[ 3]) / 2; Ez[ 2] := (Vz[ 2] + Vz[ 3]) / 2;
        Ex[ 3] := (Vx[ 3] + Vx[ 4]) / 2; Ey[ 3] := (Vy[ 3] + Vy[ 4]) / 2; Ez[ 3] := (Vz[ 3] + Vz[ 4]) / 2;
        Ex[ 4] := (Vx[ 4] + Vx[ 0]) / 2; Ey[ 4] := (Vy[ 4] + Vy[ 0]) / 2; Ez[ 4] := (Vz[ 4] + Vz[ 0]) / 2;

        Ex[ 5] := (Vx[ 0] + Vx[ 5]) / 2; Ey[ 5] := (Vy[ 0] + Vy[ 5]) / 2; Ez[ 5] := (Vz[ 0] + Vz[ 5]) / 2;
        Ex[ 6] := (Vx[ 1] + Vx[ 6]) / 2; Ey[ 6] := (Vy[ 1] + Vy[ 6]) / 2; Ez[ 6] := (Vz[ 1] + Vz[ 6]) / 2;
        Ex[ 7] := (Vx[ 2] + Vx[ 7]) / 2; Ey[ 7] := (Vy[ 2] + Vy[ 7]) / 2; Ez[ 7] := (Vz[ 2] + Vz[ 7]) / 2;
        Ex[ 8] := (Vx[ 3] + Vx[ 8]) / 2; Ey[ 8] := (Vy[ 3] + Vy[ 8]) / 2; Ez[ 8] := (Vz[ 3] + Vz[ 8]) / 2;
        Ex[ 9] := (Vx[ 4] + Vx[ 9]) / 2; Ey[ 9] := (Vy[ 4] + Vy[ 9]) / 2; Ez[ 9] := (Vz[ 4] + Vz[ 9]) / 2;

        Ex[10] := (Vx[10] + Vx[ 5]) / 2; Ey[10] := (Vy[10] + Vy[ 5]) / 2; Ez[10] := (Vz[10] + Vz[ 5]) / 2;
        Ex[11] := (Vx[11] + Vx[ 6]) / 2; Ey[11] := (Vy[11] + Vy[ 6]) / 2; Ez[11] := (Vz[11] + Vz[ 6]) / 2;
        Ex[12] := (Vx[12] + Vx[ 7]) / 2; Ey[12] := (Vy[12] + Vy[ 7]) / 2; Ez[12] := (Vz[12] + Vz[ 7]) / 2;
        Ex[13] := (Vx[13] + Vx[ 8]) / 2; Ey[13] := (Vy[13] + Vy[ 8]) / 2; Ez[13] := (Vz[13] + Vz[ 8]) / 2;
        Ex[14] := (Vx[14] + Vx[ 9]) / 2; Ey[14] := (Vy[14] + Vy[ 9]) / 2; Ez[14] := (Vz[14] + Vz[ 9]) / 2;

        Ex[15] := (Vx[10] + Vx[ 6]) / 2; Ey[15] := (Vy[10] + Vy[ 6]) / 2; Ez[15] := (Vz[10] + Vz[ 6]) / 2;
        Ex[16] := (Vx[11] + Vx[ 7]) / 2; Ey[16] := (Vy[11] + Vy[ 7]) / 2; Ez[16] := (Vz[11] + Vz[ 7]) / 2;
        Ex[17] := (Vx[12] + Vx[ 8]) / 2; Ey[17] := (Vy[12] + Vy[ 8]) / 2; Ez[17] := (Vz[12] + Vz[ 8]) / 2;
        Ex[18] := (Vx[13] + Vx[ 9]) / 2; Ey[18] := (Vy[13] + Vy[ 9]) / 2; Ez[18] := (Vz[13] + Vz[ 9]) / 2;
        Ex[19] := (Vx[14] + Vx[ 5]) / 2; Ey[19] := (Vy[14] + Vy[ 5]) / 2; Ez[19] := (Vz[14] + Vz[ 5]) / 2;

        Ex[20] := (Vx[10] + Vx[15]) / 2; Ey[20] := (Vy[10] + Vy[15]) / 2; Ez[20] := (Vz[10] + Vz[15]) / 2;
        Ex[21] := (Vx[11] + Vx[16]) / 2; Ey[21] := (Vy[11] + Vy[16]) / 2; Ez[21] := (Vz[11] + Vz[16]) / 2;
        Ex[22] := (Vx[12] + Vx[17]) / 2; Ey[22] := (Vy[12] + Vy[17]) / 2; Ez[22] := (Vz[12] + Vz[17]) / 2;
        Ex[23] := (Vx[13] + Vx[18]) / 2; Ey[23] := (Vy[13] + Vy[18]) / 2; Ez[23] := (Vz[13] + Vz[18]) / 2;
        Ex[24] := (Vx[14] + Vx[19]) / 2; Ey[24] := (Vy[14] + Vy[19]) / 2; Ez[24] := (Vz[14] + Vz[19]) / 2;

        Ex[25] := (Vx[15] + Vx[16]) / 2; Ey[25] := (Vy[15] + Vy[16]) / 2; Ez[25] := (Vz[15] + Vz[16]) / 2;
        Ex[26] := (Vx[16] + Vx[17]) / 2; Ey[26] := (Vy[16] + Vy[17]) / 2; Ez[26] := (Vz[16] + Vz[17]) / 2;
        Ex[27] := (Vx[17] + Vx[18]) / 2; Ey[27] := (Vy[17] + Vy[18]) / 2; Ez[27] := (Vz[17] + Vz[18]) / 2;
        Ex[28] := (Vx[18] + Vx[19]) / 2; Ey[28] := (Vy[18] + Vy[19]) / 2; Ez[28] := (Vz[18] + Vz[19]) / 2;
        Ex[29] := (Vx[19] + Vx[15]) / 2; Ey[29] := (Vy[19] + Vy[15]) / 2; Ez[29] := (Vz[19] + Vz[15]) / 2;
