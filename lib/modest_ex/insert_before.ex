defmodule ModestEx.InsertBefore do
  @moduledoc false

  def insert_before([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [insert_before(bin, selector, new_bin)] ++ insert_before(rest, selector, new_bin)
  end

  def insert_before([], _, _), do: []

  def insert_before(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.LexborHelper.ensure_started()

    scope = Application.get_env(:modest_ex, :scope, :body_children)

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, _num_matches} <- :lexbor_erl.insert_before_content(doc, selector, new_bin),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, scope)
    else
      {:error, _reason} = error ->
        error

      error ->
        {:error, error}
    end
  end
end
