// <!-- Boris(2024). Cuboid from cubic parts X*Y*Z, must be defined: W, X, Y, Z -->

        if not VarExists('Thiñkness') then
            Thickness := 0.2;

        NMax := Max(Max( X, Y), Z);
        NMin := Min(Min( X, Y), Z);

        OddX := X mod 2;
        OddY := Y mod 2;
        OddZ := Z mod 2;

        Ax := Pi;
        Ay := Pi;
        Az := Pi;
        if NMin = 1 then begin
            Nx := X;
            Ny := Y;
            Nz := Z;
            NDif := 0;
        end else if (OddX = OddY) and (OddY = OddZ) then begin
            Nx := NMax;
            Ny := NMax;
            Nz := NMax;
            NDif := NMax - NMin;
            Ax := Pi / 2;
            Ay := Pi / 2;
            Az := Pi / 2;
        end else if OddX = OddY then begin
            Nx := Max( X, Y);
            Ny := Nx;
            Nz := Z;
            NDif := Nx - Min( X, Y);
            Az := Pi / 2;
        end else if OddY = OddZ then begin
            Nx := X;
            Ny := Max( Y, Z);
            Nz := Ny;
            NDif := Ny - Min( Y, Z);
            Ax := Pi / 2;
        end else if OddZ = OddX then begin
            Nx := Max( Z, X);
            Ny := Y;
            Nz := Nx;
            NDif := Nx - Min( Z, X);
            Ay := Pi / 2;
        end;

        if not VarExists('Oversize') then
            Oversize := Max(0., NDif / 2 - 1 + Thickness);

        WD := W / (NMax + 2 * Oversize);

        DX[0] := -W; // if Nx = 1
        DY[0] := -W;
        DZ[0] := -W;

        for i := 0 to Nx - 2 do
            DX[i] := WD * (2 * i - Nx + 2);
        for i := 0 to Ny - 2 do
            DY[i] := WD * (2 * i - Ny + 2);
        for i := 0 to Nz - 2 do
            DZ[i] := WD * (2 * i - Nz + 2);

        Wx := WD * (X + Oversize * Min(X, 2));
        Wy := WD * (Y + Oversize * Min(Y, 2));
        Wz := WD * (Z + Oversize * Min(Z, 2));
