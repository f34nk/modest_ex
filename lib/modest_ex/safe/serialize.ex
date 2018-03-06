defmodule ModestEx.Safe.Serialize do
  @moduledoc false
  
  def serialize(bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:serialize, bin <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:serialize, result}} -> result
      _ -> {:error, bin}
    end
  end

end