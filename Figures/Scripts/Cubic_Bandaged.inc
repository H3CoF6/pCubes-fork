        include 'Figures\Scripts\Cube_Standard_Colors.inc';

        WD := 2 * W / N;
        D[0] := -W + WD;
        for i := 1 to N - 2 do
            D[i] := D[i-1] + WD;

        pCount := 0;

        procedure ParseCoords();
        begin
          p := Pos(',', sCubie);
          if p = 0 then
            p := Length(sCubie) + 1;

          Coords := HexToInt(Trim(copy(sCubie, 1, p-1)));
          Delete(sCubie, 1, p);

          x := Coords shr 8;
          y := (Coords shr 4) and 15;
          z := Coords and 15;

          SizesX[pCount] := wx;
          SizesY[pCount] := wy;
          SizesZ[pCount] := wz;
          CoordX[pCount] := x;
          CoordY[pCount] := y;
          CoordZ[pCount] := z;
          Inc(pCount);
        end;

        procedure ParseTxt(sCubie);
        begin
          p := Pos('=', sCubie);
          Sizes := HexToInt(Trim(copy(sCubie, 1, p-1)));
          Delete(sCubie, 1, p);

          wx := Sizes shr 8;
          wy := (Sizes shr 4) and 15;
          wz := Sizes and 15;

          while Length(sCubie) > 2 do
              ParseCoords;
        end;
