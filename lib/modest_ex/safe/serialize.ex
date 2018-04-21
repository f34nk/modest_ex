defmodule ModestEx.Safe.Serialize do
  @moduledoc false
  
  def serialize(bin, scope) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:serialize, bin <> "\0", ModestEx.to_scope(scope) <> "\0"}) do
      {:ok, {:serialize, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end

end