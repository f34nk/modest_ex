defmodule ModestEx.Safe.Wrap do
   @moduledoc false
  
  def wrap(bin, selector, new_bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:wrap, bin <> "\0", selector <> "\0", new_bin <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:wrap, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end
end