defmodule ModestEx.Safe.Prepend do
   @moduledoc false
  
  def prepend(bin, selector, new_bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:prepend, bin <> "\0", selector <> "\0", new_bin <> "\0"}) do
      {:ok, {:prepend, reply}} -> 
        case reply do
          <<"<-undef>"::utf8>> <> result -> result
          _ -> {:error, reply}
        end
      _ -> {:error, bin}
    end
  end
end