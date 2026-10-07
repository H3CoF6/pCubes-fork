        if not VarExists('R') then
          R := 1;

        phi := (sqrt(5) - 1) / 2; // The golden ratio
        a := R / sqrt(3);
        b := a / phi;
        c := a * phi;

        dAngle := Arctan(phi) + Arctan(1 - phi);
        dAngle2 := Arctan(phi) - Arctan(1 - phi);

        Rsin := R * sin(dAngle); // R * sqrt((5 + 2 * sqrt(5)) / 15);
        Rcos := R * cos(dAngle); // R * sqrt((10 - 2 * sqrt(5)) / 15);
        R2sin := R * sin(dAngle2); // R * sqrt((5 - 2 * sqrt(5)) / 15);
        R2cos := R * cos(dAngle2); // R * sqrt((10 + 2 * sqrt(5)) / 15);

        sAngle := 2 * Pi / 5;

        // Vertices (corners)

        Vx[ 0] := 0; Vy[ 0] := c; Vz[ 0] := b;
        Vx[ 1] := 0; Vy[ 1] :=-c; Vz[ 1] := b;
        Vx[ 2] := 0; Vy[ 2] :=-c; Vz[ 2] :=-b;
        Vx[ 3] := 0; Vy[ 3] := c; Vz[ 3] :=-b;
        Vx[ 4] := c; Vy[ 4] := b; Vz[ 4] := 0;
        Vx[ 5] :=-c; Vy[ 5] := b; Vz[ 5] := 0;
        Vx[ 6] :=-c; Vy[ 6] :=-b; Vz[ 6] := 0;
        Vx[ 7] := c; Vy[ 7] :=-b; Vz[ 7] := 0;
        Vx[ 8] := b; Vy[ 8] := 0; Vz[ 8] := c;
        Vx[ 9] := b; Vy[ 9] := 0; Vz[ 9] :=-c;
        Vx[10] :=-b; Vy[10] := 0; Vz[10] :=-c;
        Vx[11] :=-b; Vy[11] := 0; Vz[11] := c;
        Vx[12] := a; Vy[12] := a; Vz[12] := a;
        Vx[13] := a; Vy[13] := a; Vz[13] :=-a;
        Vx[14] := a; Vy[14] :=-a; Vz[14] := a;
        Vx[15] := a; Vy[15] :=-a; Vz[15] :=-a;
        Vx[16] :=-a; Vy[16] := a; Vz[16] := a;
        Vx[17] :=-a; Vy[17] := a; Vz[17] :=-a;
        Vx[18] :=-a; Vy[18] :=-a; Vz[18] := a;
        Vx[19] :=-a; Vy[19] :=-a; Vz[19] :=-a;

        // Centers
        aa := (2 * (a + b) + c) / 5; // R * sqrt((7 + 3 * sqrt(5)) / 30)
        ba := (b + 2 * a) / 5; // R * sqrt((3 + sqrt(5)) / 30)

        Cx[ 0] := ba; Cy[ 0] :=  0; Cz[ 0] := aa;
        Cx[ 1] := aa; Cy[ 1] := ba; Cz[ 1] :=  0;
        Cx[ 2] := aa; Cy[ 2] :=-ba; Cz[ 2] :=  0;
        Cx[ 3] :=  0; Cy[ 3] :=-aa; Cz[ 3] := ba;
        Cx[ 4] :=-ba; Cy[ 4] :=  0; Cz[ 4] := aa;
        Cx[ 5] :=  0; Cy[ 5] := aa; Cz[ 5] := ba;
        Cx[ 6] :=-aa; Cy[ 6] :=-ba; Cz[ 6] :=  0;
        Cx[ 7] :=-aa; Cy[ 7] := ba; Cz[ 7] :=  0;
        Cx[ 8] :=  0; Cy[ 8] := aa; Cz[ 8] :=-ba;
        Cx[ 9] := ba; Cy[ 9] :=  0; Cz[ 9] :=-aa;
        Cx[10] :=  0; Cy[10] :=-aa; Cz[10] :=-ba;
        Cx[11] :=-ba; Cy[11] :=  0; Cz[11] :=-aa;

        // Edges
        e0 := a / 2;
        e1 := (c + a) / 2;
        e2 := (b + a) / 2;

        Ex[ 0] := b; Ey[ 0] := 0; Ez[ 0] := 0;
        Ex[ 1] :=-b; Ey[ 1] := 0; Ez[ 1] := 0;
        Ex[ 2] := 0; Ey[ 2] := b; Ez[ 2] := 0;
        Ex[ 3] := 0; Ey[ 3] :=-b; Ez[ 3] := 0;
        Ex[ 4] := 0; Ey[ 4] := 0; Ez[ 4] := b;
        Ex[ 5] := 0; Ey[ 5] := 0; Ez[ 5] :=-b;

        Ex[ 6] := e0; Ey[ 6] := e1; Ez[ 6] := e2;
        Ex[ 7] :=-e0; Ey[ 7] := e1; Ez[ 7] := e2;
        Ex[ 8] := e0; Ey[ 8] :=-e1; Ez[ 8] := e2;
        Ex[ 9] :=-e0; Ey[ 9] :=-e1; Ez[ 9] := e2;
        Ex[10] := e0; Ey[10] := e1; Ez[10] :=-e2;
        Ex[11] :=-e0; Ey[11] := e1; Ez[11] :=-e2;
        Ex[12] := e0; Ey[12] :=-e1; Ez[12] :=-e2;
        Ex[13] :=-e0; Ey[13] :=-e1; Ez[13] :=-e2;

        Ex[14] := e2; Ey[14] := e0; Ez[14] := e1;
        Ex[15] := e2; Ey[15] :=-e0; Ez[15] := e1;
        Ex[16] := e2; Ey[16] := e0; Ez[16] :=-e1;
        Ex[17] := e2; Ey[17] :=-e0; Ez[17] :=-e1;
        Ex[18] :=-e2; Ey[18] := e0; Ez[18] := e1;
        Ex[19] :=-e2; Ey[19] :=-e0; Ez[19] := e1;
        Ex[20] :=-e2; Ey[20] := e0; Ez[20] :=-e1;
        Ex[21] :=-e2; Ey[21] :=-e0; Ez[21] :=-e1;

        Ex[22] := e1; Ey[22] := e2; Ez[22] := e0;
        Ex[23] := e1; Ey[23] := e2; Ez[23] :=-e0;
        Ex[24] :=-e1; Ey[24] := e2; Ez[24] := e0;
        Ex[25] :=-e1; Ey[25] := e2; Ez[25] :=-e0;
        Ex[26] := e1; Ey[26] :=-e2; Ez[26] := e0;
        Ex[27] := e1; Ey[27] :=-e2; Ez[27] :=-e0;
        Ex[28] :=-e1; Ey[28] :=-e2; Ez[28] := e0;
        Ex[29] :=-e1; Ey[29] :=-e2; Ez[29] :=-e0;
