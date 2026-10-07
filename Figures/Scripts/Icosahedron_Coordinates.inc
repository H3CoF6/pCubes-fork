        // Vertices (corners)

        if not VarExists('R') then
          R := 1;

        mAngle := ArcTan(0.5);
        Rsin := R * sin(mAngle); // R / sqrt(5);
        Rcos := R * cos(mAngle); // R * 2 / sqrt(5);
        sAngle := PI * 2 / 5;

        Vx[0] := 0;
        Vy[0] := 0;
        Vz[0] := R;
        for i := 1 to 5 do begin
            Vx[i] := Rcos * sin(sAngle * (i - 1));
            Vy[i] := Rcos * cos(sAngle * (i - 1));
            Vz[i] := Rsin;
        end;
        for i := 6 to 10 do begin
            Vx[i] := Rcos * sin(sAngle * (i - 0.5));
            Vy[i] := Rcos * cos(sAngle * (i - 0.5));
            Vz[i] := -Rsin;
        end;
        Vx[11] :=  0;
        Vy[11] :=  0;
        Vz[11] := -R;


        // Centers

        dAngle := (Arctan(2) + Arcsin(2/3)) / 2;
        dAngle2 := (Arctan(2) - Arcsin(2/3)) / 2;
        //phi := (Sqrt(5) - 1) / 2; // The golden ratio
        //dAngle := Arctan(phi) + Arctan(1 - phi);
        //dAngle2 := Arctan(phi) - Arctan(1 - phi);

        Rin := R * sin(dAngle); // R * sqrt((5 + 2 * sqrt(5)) / 15);
        RsinI := Rin * sin(dAngle); // Rin * sqrt((5 + 2 * sqrt(5)) / 15);
        RcosI := Rin * cos(dAngle); // Rin * sqrt((10 - 2 * sqrt(5)) / 15);
        R2sinI := Rin * sin(dAngle2); // Rin * sqrt((5 - 2 * sqrt(5)) / 15);
        R2cosI := Rin * cos(dAngle2); // Rin * sqrt((10 + 2 * sqrt(5)) / 15);
        sAngle := PI * 2 / 5;

        for i := 0 to 4 do begin
            Cx[i] := RcosI * sin(sAngle * (i - 0.5));
            Cy[i] := RcosI * cos(sAngle * (i - 0.5));
            Cz[i] := RsinI;
        end;

        for i := 5 to 9 do begin
            Cx[i] := R2cosI * sin(sAngle * (i - 0.5));
            Cy[i] := R2cosI * cos(sAngle * (i - 0.5));
            Cz[i] := R2sinI;
        end;

        for i := 10 to 19 do begin
            Cx[i] := -Cx[i - 10];
            Cy[i] := -Cy[i - 10];
            Cz[i] := -Cz[i - 10];
        end;


        // Edges

        Ex[ 0] := (Vx[ 0] + Vx[ 1]) / 2; Ey[ 0] := (Vy[ 0] + Vy[ 1]) / 2; Ez[ 0] := (Vz[ 0] + Vz[ 1]) / 2;
        Ex[ 1] := (Vx[ 0] + Vx[ 2]) / 2; Ey[ 1] := (Vy[ 0] + Vy[ 2]) / 2; Ez[ 1] := (Vz[ 0] + Vz[ 2]) / 2;
        Ex[ 2] := (Vx[ 0] + Vx[ 3]) / 2; Ey[ 2] := (Vy[ 0] + Vy[ 3]) / 2; Ez[ 2] := (Vz[ 0] + Vz[ 3]) / 2;
        Ex[ 3] := (Vx[ 0] + Vx[ 4]) / 2; Ey[ 3] := (Vy[ 0] + Vy[ 4]) / 2; Ez[ 3] := (Vz[ 0] + Vz[ 4]) / 2;
        Ex[ 4] := (Vx[ 0] + Vx[ 5]) / 2; Ey[ 4] := (Vy[ 0] + Vy[ 5]) / 2; Ez[ 4] := (Vz[ 0] + Vz[ 5]) / 2;

        Ex[ 5] := (Vx[ 1] + Vx[ 2]) / 2; Ey[ 5] := (Vy[ 1] + Vy[ 2]) / 2; Ez[ 5] := (Vz[ 1] + Vz[ 2]) / 2;
        Ex[ 6] := (Vx[ 2] + Vx[ 3]) / 2; Ey[ 6] := (Vy[ 2] + Vy[ 3]) / 2; Ez[ 6] := (Vz[ 2] + Vz[ 3]) / 2;
        Ex[ 7] := (Vx[ 3] + Vx[ 4]) / 2; Ey[ 7] := (Vy[ 3] + Vy[ 4]) / 2; Ez[ 7] := (Vz[ 3] + Vz[ 4]) / 2;
        Ex[ 8] := (Vx[ 4] + Vx[ 5]) / 2; Ey[ 8] := (Vy[ 4] + Vy[ 5]) / 2; Ez[ 8] := (Vz[ 4] + Vz[ 5]) / 2;
        Ex[ 9] := (Vx[ 5] + Vx[ 1]) / 2; Ey[ 9] := (Vy[ 5] + Vy[ 1]) / 2; Ez[ 9] := (Vz[ 5] + Vz[ 1]) / 2;

        Ex[10] := (Vx[ 1] + Vx[ 6]) / 2; Ey[10] := (Vy[ 1] + Vy[ 6]) / 2; Ez[10] := (Vz[ 1] + Vz[ 6]) / 2;
        Ex[11] := (Vx[ 2] + Vx[ 7]) / 2; Ey[11] := (Vy[ 2] + Vy[ 7]) / 2; Ez[11] := (Vz[ 2] + Vz[ 7]) / 2;
        Ex[12] := (Vx[ 3] + Vx[ 8]) / 2; Ey[12] := (Vy[ 3] + Vy[ 8]) / 2; Ez[12] := (Vz[ 3] + Vz[ 8]) / 2;
        Ex[13] := (Vx[ 4] + Vx[ 9]) / 2; Ey[13] := (Vy[ 4] + Vy[ 9]) / 2; Ez[13] := (Vz[ 4] + Vz[ 9]) / 2;
        Ex[14] := (Vx[ 5] + Vx[10]) / 2; Ey[14] := (Vy[ 5] + Vy[10]) / 2; Ez[14] := (Vz[ 5] + Vz[10]) / 2;

        Ex[15] := (Vx[ 1] + Vx[10]) / 2; Ey[15] := (Vy[ 1] + Vy[10]) / 2; Ez[15] := (Vz[ 1] + Vz[10]) / 2;
        Ex[16] := (Vx[ 2] + Vx[ 6]) / 2; Ey[16] := (Vy[ 2] + Vy[ 6]) / 2; Ez[16] := (Vz[ 2] + Vz[ 6]) / 2;
        Ex[17] := (Vx[ 3] + Vx[ 7]) / 2; Ey[17] := (Vy[ 3] + Vy[ 7]) / 2; Ez[17] := (Vz[ 3] + Vz[ 7]) / 2;
        Ex[18] := (Vx[ 4] + Vx[ 8]) / 2; Ey[18] := (Vy[ 4] + Vy[ 8]) / 2; Ez[18] := (Vz[ 4] + Vz[ 8]) / 2;
        Ex[19] := (Vx[ 5] + Vx[ 9]) / 2; Ey[19] := (Vy[ 5] + Vy[ 9]) / 2; Ez[19] := (Vz[ 5] + Vz[ 9]) / 2;

        Ex[20] := (Vx[ 6] + Vx[ 7]) / 2; Ey[20] := (Vy[ 6] + Vy[ 7]) / 2; Ez[20] := (Vz[ 6] + Vz[ 7]) / 2;
        Ex[21] := (Vx[ 7] + Vx[ 8]) / 2; Ey[21] := (Vy[ 7] + Vy[ 8]) / 2; Ez[21] := (Vz[ 7] + Vz[ 8]) / 2;
        Ex[22] := (Vx[ 8] + Vx[ 9]) / 2; Ey[22] := (Vy[ 8] + Vy[ 9]) / 2; Ez[22] := (Vz[ 8] + Vz[ 9]) / 2;
        Ex[23] := (Vx[ 9] + Vx[10]) / 2; Ey[23] := (Vy[ 9] + Vy[10]) / 2; Ez[23] := (Vz[ 9] + Vz[10]) / 2;
        Ex[24] := (Vx[10] + Vx[ 6]) / 2; Ey[24] := (Vy[10] + Vy[ 6]) / 2; Ez[24] := (Vz[10] + Vz[ 6]) / 2;

        Ex[25] := (Vx[11] + Vx[ 6]) / 2; Ey[25] := (Vy[11] + Vy[ 6]) / 2; Ez[25] := (Vz[11] + Vz[ 6]) / 2;
        Ex[26] := (Vx[11] + Vx[ 7]) / 2; Ey[26] := (Vy[11] + Vy[ 7]) / 2; Ez[26] := (Vz[11] + Vz[ 7]) / 2;
        Ex[27] := (Vx[11] + Vx[ 8]) / 2; Ey[27] := (Vy[11] + Vy[ 8]) / 2; Ez[27] := (Vz[11] + Vz[ 8]) / 2;
        Ex[28] := (Vx[11] + Vx[ 9]) / 2; Ey[28] := (Vy[11] + Vy[ 9]) / 2; Ez[28] := (Vz[11] + Vz[ 9]) / 2;
        Ex[29] := (Vx[11] + Vx[10]) / 2; Ey[29] := (Vy[11] + Vy[10]) / 2; Ez[29] := (Vz[11] + Vz[10]) / 2;
        
                                                                               