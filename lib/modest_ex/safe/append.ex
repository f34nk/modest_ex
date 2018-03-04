defmodule ModestEx.Safe.Append do
   @moduledoc false
  
  def append(bin, selector, new_bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:append, bin <> "\0", selector <> "\0", new_bin <> "\0"}) do
      {:ok, {:append, reply}} -> 
        case reply do
          <<"<-undef>"::utf8>> <> result -> result
          _ -> {:error, reply}
        end
      _ -> {:error, bin}
    end
  end
end