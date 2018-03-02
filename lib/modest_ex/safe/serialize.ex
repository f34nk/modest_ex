defmodule ModestEx.Safe.Serialize do
  def serialize(bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:serialize, bin <> "\0"}) do
      {:ok, {:serialize, reply}} -> 
        case reply do
          <<"<-undef>"::utf8>> <> result -> result
          _ -> {:error, reply}
        end
      _ -> {:error, bin}
    end
  end
end