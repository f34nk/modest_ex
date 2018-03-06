defmodule ModestEx.Safe.Replace do
   @moduledoc false
  
  def replace(bin, selector, new_bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:replace, bin <> "\0", selector <> "\0", new_bin <> "\0"}) do
      {:ok, {:replace, reply}} -> 
        case reply do
          <<"<-undef>"::utf8>> <> result -> result
          _ -> {:error, reply}
        end
      _ -> {:error, bin}
    end
  end
end