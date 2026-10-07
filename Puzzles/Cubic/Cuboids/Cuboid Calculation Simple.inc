// <!-- Boris(2024). Cuboid from cubic parts X*Y*Z, must be defined: X, Y, Z, W -->


        if not VarExists('Oversize') then
            Oversize := 0;

        N := Max(Max( X, Y), Z);
        WD := W / (N + 2 * Oversize);
        Wx := WD * (X + Oversize * Min(X, 2));
        Wy := WD * (Y + Oversize * Min(Y, 2));
        Wz := WD * (Z + Oversize * Min(Z, 2));

        for i := 0 to X - 2 do
            DX[i] := WD * (2 * i - X + 2);
        for i := 0 to Y - 2 do
            DY[i] := WD * (2 * i - Y + 2);
        for i := 0 to Z - 2 do
            DZ[i] := WD * (2 * i - Z + 2);
