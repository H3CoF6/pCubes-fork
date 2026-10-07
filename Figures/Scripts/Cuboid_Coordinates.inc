        if not VarExists('W') then
            W := 0.5;
        if not VarExists('WX') then
            WX := W;
        if not VarExists('WY') then
            WY := W;
        if not VarExists('WZ') then
            WZ := W;
        if not VarExists('DWX') then
            DWX := 0;
        if not VarExists('DWY') then
            DWY := 0;
        if not VarExists('DWZ') then
            DWZ := 0;


        // Vertices (corners)

        Vx[0] :=-WX + DWX; Vy[0] :=-WY + DWY; Vz[0] :=-WZ + DWZ;
        Vx[1] :=-WX + DWX; Vy[1] :=-WY + DWY; Vz[1] := WZ + DWZ;
        Vx[2] :=-WX + DWX; Vy[2] := WY + DWY; Vz[2] :=-WZ + DWZ;
        Vx[3] :=-WX + DWX; Vy[3] := WY + DWY; Vz[3] := WZ + DWZ;
        Vx[4] := WX + DWX; Vy[4] :=-WY + DWY; Vz[4] :=-WZ + DWZ;
        Vx[5] := WX + DWX; Vy[5] :=-WY + DWY; Vz[5] := WZ + DWZ;
        Vx[6] := WX + DWX; Vy[6] := WY + DWY; Vz[6] :=-WZ + DWZ;
        Vx[7] := WX + DWX; Vy[7] := WY + DWY; Vz[7] := WZ + DWZ;


        // Centers
        Cx[0] :=-WX + DWX; Cy[0] :=      DWY; Cz[0] :=      DWZ;
        Cx[1] := WX + DWX; Cy[1] :=      DWY; Cz[1] :=      DWZ;
        Cx[2] :=      DWX; Cy[2] :=-WY + DWY; Cz[2] :=      DWZ;
        Cx[3] :=      DWX; Cy[3] := WY + DWY; Cz[3] :=      DWZ;
        Cx[4] :=      DWX; Cy[4] :=      DWY; Cz[4] :=-WZ + DWZ;
        Cx[5] :=      DWX; Cy[5] :=      DWY; Cz[5] := WZ + DWZ;


        // Edges

        Ex[ 0] :=      DWX; Ey[ 0] :=-WY + DWY; Ez[ 0] := WZ + DWZ;
        Ex[ 1] :=      DWX; Ey[ 1] := WY + DWY; Ez[ 1] := WZ + DWZ;
        Ex[ 2] :=-WX + DWX; Ey[ 2] :=      DWY; Ez[ 2] := WZ + DWZ;
        Ex[ 3] := WX + DWX; Ey[ 3] :=      DWY; Ez[ 3] := WZ + DWZ;
        Ex[ 4] := WX + DWX; Ey[ 4] :=-WY + DWY; Ez[ 4] :=      DWZ;
        Ex[ 5] := WX + DWX; Ey[ 5] := WY + DWY; Ez[ 5] :=      DWZ;
        Ex[ 6] :=      DWX; Ey[ 6] := WY + DWY; Ez[ 6] :=-WZ + DWZ;
        Ex[ 7] :=      DWX; Ey[ 7] :=-WY + DWY; Ez[ 7] :=-WZ + DWZ;
        Ex[ 8] := WX + DWX; Ey[ 8] :=      DWY; Ez[ 8] :=-WZ + DWZ;
        Ex[ 9] :=-WX + DWX; Ey[ 9] :=      DWY; Ez[ 9] :=-WZ + DWZ;
        Ex[10] :=-WX + DWX; Ey[10] := WY + DWY; Ez[10] :=      DWZ;
        Ex[11] :=-WX + DWX; Ey[11] :=-WY + DWY; Ez[11] :=      DWZ;
