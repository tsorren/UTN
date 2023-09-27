   infoLS.idVendedor = auxArch.idVendedor;
        infoLS.cantVendida = auxArch.cantVendida;

        nodoLP* NodoActualLP = InsertarSinRepetir(LP, infoLP);

        InsertarOrdenado(NodoActualLP->info.ptrLS, infoLS);
    }

    MostrarListaDeListas(LP);
