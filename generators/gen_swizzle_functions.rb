require 'erb'

TEMPLATE = %{
<% (1..4).each do |i| %>
<% [:x, :y, :z, :w].repeated_permutation(i) do |p| %>
// return a vector swizzled to <%= p.join %>
template<typename = void>
requires vector_size_at_least<size, %= required_vector_size(p)> %><size>
constexpr vector<%= i %>_type <%= p.join %>() const
{

}
<% end %>
<% end %>
}

def required_vector_size(set)
  return 4 if set.include?(:w)
  return 3 if set.include?(:z)
  return 2 if set.include?(:y)
  return 1
end

template = ERB.new(TEMPLATE)
puts template.result(binding)