defmodule ModestEx.Safe.Remove do
   @moduledoc false
  
  def remove(bin, selector) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:remove, bin <> "\0", selector <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:remove, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end
end