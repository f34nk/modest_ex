defmodule ModestEx.Safe.Prepend do
   @moduledoc false
  
  def prepend(bin, selector, new_bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:prepend, bin <> "\0", selector <> "\0", new_bin <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:prepend, result}} -> result
      _ -> {:error, bin}
    end
  end
end