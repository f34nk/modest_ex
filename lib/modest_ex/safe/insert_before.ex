defmodule ModestEx.Safe.InsertBefore do
   @moduledoc false
  
  def insert_before(bin, selector, new_bin) do
    case Nodex.Cnode.call(ModestEx.Safe.Cnode, {:insert_before, bin <> "\0", selector <> "\0", new_bin <> "\0", ModestEx.scope() <> "\0"}) do
      {:ok, {:insert_before, result}} -> ModestEx.resolve(result)
      _ -> {:error, bin}
    end
  end
end