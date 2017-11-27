#pragma once

void setupNpc();

int npcShape;//0 = aabb 1 = circle 2 = ray
c2AABB aabb_npc_info;
c2Circle circle_npc_info;
c2Ray ray_npc_info;

sf::RectangleShape aabb_npc;
sf::CircleShape circle_npc;
sf::VertexArray ray_npc(sf::Lines);

int mouseShape;//0 = aabb 1 = circle 2 = ray 3 = capsule 4 = polygon
c2AABB aabb_mouse_info;


sf::Sprite aabb_mouse;