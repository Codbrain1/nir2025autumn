#pragma once
namespace DirectSumm
{
namespace KDK
{
template <class T>
void next_step(T& ps)
{
}
template <class T>
void calculate_forces(T& ps)
{
}
template <class T>
void calculate_conversation_laws(T&)
{
}
template <class T>
void next_step_parallOMP(T& ps)
{
}
template <class T>
void calculate_forces_parallOMP(T& ps)
{
}
template <class T>
void calculate_conversation_laws_parallOMP(T& ps)
{
}
template <class T>
void next_step_parallCUDA(T& ps)
{
}
template <class T>
void calculate_forces_parallCUDA(T& ps)
{
}
template <class T>
void calculate_conversation_laws_parallCUDA(T& ps)
{
}
}  // namespace KDK
}  // namespace DirectSumm