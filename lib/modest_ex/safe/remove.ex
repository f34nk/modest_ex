defmodule ModestEx.Safe.Remove do
   @moduledoc false
  
  def remove(bin, selector) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:remove, bin <> "\0", selector <> "\0"}) do
      {:ok, {:remove, reply}} -> 
        case reply do
          <<"<-undef>"::utf8>> <> result -> result
          _ -> {:error, reply}
        end
      _ -> {:error, bin}
    end
  end
end