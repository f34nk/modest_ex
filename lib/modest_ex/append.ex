defmodule ModestEx.Append do
  @moduledoc false

  def append([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [append(bin, selector, new_bin)] ++ append(rest, selector, new_bin)
  end

  def append([], _, _), do: []

  def append(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.LexborHelper.ensure_started()

    scope = Application.get_env(:modest_ex, :scope, :body_children)

    # Handle special case for "body" selector - lexbor_erl's append_content
    # starts search from inside body, so it can't match the body element itself
    if selector == "body" do
      append_to_body(bin, new_bin, scope)
    else
      with {:ok, doc} <- :lexbor_erl.parse(bin),
           {:ok, _num_matches} <- :lexbor_erl.append_content(doc, selector, new_bin),
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

  # Special handling for body selector using select + inner_html + set_inner_html
  defp append_to_body(bin, new_bin, scope) do
    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, [body_node | _]} <- :lexbor_erl.select(doc, "body"),
         {:ok, current_inner} <- :lexbor_erl.inner_html(doc, body_node),
         :ok <- :lexbor_erl.set_inner_html(doc, body_node, current_inner <> new_bin),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, scope)
    else
      {:ok, []} ->
        # No body found, return as-is
        bin

      {:error, _reason} = error ->
        error

      error ->
        {:error, error}
    end
  end
end
